require('dotenv').config();

// Server module
const express = require('express');
const bodyParser = require('body-parser');
const app = express();

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

// Modules
const mysql = require('mysql2/promise');
const bcrypt = require('bcrypt');

// Main endpoint
app.get('/', async (req, res) => {
    res.send('Hello World!');
});


//-------------------------------------------------------------------//
//                                                                   //
//                            API USUARIO                            //
//                                                                   //
//-------------------------------------------------------------------//

// [GET] Users endpoint
app.get('/users', async (req, res) => {
    res.status(200).json(await queryDb('SELECT * FROM User'));
});

app.post('/user', async (req, res) => {
    const dni = req.body.dni;
    const user = await queryDb(`SELECT id, username, dni, userrange_id FROM User WHERE dni like '${dni}'`);
    
    res.status(200).json(user);
});

app.post('/users/edit', async (req, res) => {
    const userData = req.body;
    const token = req.body.token;
    
    const reqUser = (await queryDb(`SELECT User.id, userrange_id FROM UserSession LEFT JOIN User ON User.id=UserSession.user_id WHERE token like '${token}'`))[0];
    const editUser = (await queryDb(`SELECT * FROM User WHERE dni like '${userData.dni}'`))[0];
    if (reqUser.userrange_id == 4 || reqUser.id == editUser.id) { // Check permissions

        let newName = userData.nombre == ''  ? editUser.username : userData.nombre;
        let newPass = userData.contrasena == ''  ? editUser.password :  bcrypt.hashSync(userData.contrasena, 10);

        await queryDb(`UPDATE User SET username='${newName}', password='${newPass}' WHERE id=${editUser.id}`);
        res.status(200).json({'message': 'Usuario modificado!'});
    }
    else {
        res.status(403).json({'message': 'Acceso denegado!'});
    }
});

app.post('/users/delete', async (req, res) => {
    const dni = req.body.dni;
    const token = req.body.token;
    
    const user = (await queryDb(`SELECT userrange_id, User.id, dni FROM UserSession LEFT JOIN User ON User.id=UserSession.user_id WHERE token like '${token}'`))[0];
    const deleteUser = (await queryDb(`SELECT id FROM User WHERE dni like '${dni}'`))[0]
    if (user.userrange_id == 4 || deleteUser.id == user.id) {
        await queryDb(`DELETE FROM UserCourse WHERE user_id=${deleteUser.id}`);
        await queryDb(`DELETE FROM UserSession WHERE user_id=${deleteUser.id}`);
        await queryDb(`DELETE FROM User WHERE id=${deleteUser.id}`);
        res.status(200).json({'message': 'Usuario eliminado!'});
    }
    else {
        res.status(403).json({'message': 'Acceso denegado!'});
    }

});

app.post('/login', async (req, res) => {
    const data = req.body;

    // Data "validation"
    if (data.username && data.password) {
        const session = await login(data.username, data.password);
        if (session == null) {
            res.status(400).send('User doesn\'t exists!');
        }
        else {
            res.status(200).json(session);
        }
    }
    else {
        res.status(500).send('Something went wrong');
    }
});

app.post('/logout', async (req, res) => {
    const token = req.body.token;
    await queryDb(`DELETE FROM UserSession WHERE token like '${token}'`);
    res.status(200).json({'message': 'Sesion cerrada'});
});

app.post('/register', async (req, res) => {
    const data = req.body;

    // Data "validation"
    if (data.dni && data.username && data.password) {
        // Check if user exists
        let users = await queryDb(`SELECT dni FROM User WHERE dni like '${data.dni}'`);
        if (users.length > 0) {
            res.status(409).send('DNI already exists!');
        }
        else {
            // Hash the password and insert the user into the DB
            const hashedPW = bcrypt.hashSync(data.password, 10);
            const result = await queryDb(`INSERT INTO User (username, password, dni) VALUES ('${data.username}', '${hashedPW}', '${data.dni}')`);
            
            // Login the user
            if (!data.token) {
                let userId = result.insertId;
                const session = await login(data.username, data.password);
                
                if (session == null) {
                    res.status(500).send('Something went wrong!');
                }
                else {
                    res.status(200).json(session);
                }
            }
            else {
                res.status(200).json({'message': 'Usuario registrado!'});
            }
        }
    }
    else {
        res.status(500).send('Something went wrong!');
    }

});




//-------------------------------------------------------------------//
//                                                                   //
//                            API CURSOS                             //
//                                                                   //
//-------------------------------------------------------------------//

app.post('/course', async (req, res) => {
    const courseid = req.body.courseid;
    let course = await queryDb(`SELECT * FROM Course WHERE id=${courseid}`);
    course[0].startDate = course[0].startDate.toISOString().slice(0, 10);
    course[0].finishDate = course[0].finishDate.toISOString().slice(0, 10)
    
    const matriculados = await queryDb(`SELECT User.username FROM UserCourse LEFT JOIN User ON User.id = UserCourse.user_id WHERE UserCourse.course_id=${courseid}`);
    course[0].matriculados = matriculados;

    res.status(200).json(course);
});

app.post('/course/stats', async (req, res) => {
    const courseid = req.body.courseid;
    let courseStats = await queryDb(`SELECT * FROM v_CourseStats WHERE id=${courseid}`);
    
    res.status(200).json(courseStats[0]);
});

app.post('/course/resources', async (req, res) => {
    const courseid = req.body.courseid;
    let resources = await queryDb(`SELECT Resource.id, Resource.classroom, Resource.capacity, CourseResource.from, CourseResource.to FROM CourseResource LEFT JOIN Resource ON Resource.id=CourseResource.resource_id WHERE CourseResource.course_id=${courseid}`);
    res.status(200).json(resources);
});

app.get('/resources', async (req, res) => {
    let resources = await queryDb(`SELECT * FROM Resource`);
    res.status(200).json(resources);
});

app.post('/resources/add', async (req, res) => {
    const resourceData = req.body;
    const token = req.body.token;
    
    const user = (await queryDb(`SELECT userrange_id FROM UserSession LEFT JOIN User ON User.id=UserSession.user_id WHERE token like '${token}'`))[0];
    if (user.userrange_id == 4 || user.userrange_id == 3) { //if admin
        const insertResult = await queryDb(`INSERT INTO Resource (classroom, capacity) VALUES ('${resourceData.aula}', ${resourceData.capacidad})`);
        if (insertResult.affectedRows > 0) {
            res.status(200).json({'message': 'Recurso creado correctamente!'});
        }
        else {
            res.status(500).json({'message': 'Algo salio mal!'});
        }
    }
    else {
        res.status(403).json({'message': 'Acceso denegado!'});
    }
});

app.post('/resources/edit', async (req, res) => {
    const resourceData = req.body;
    const token = req.body.token;
    
    const user = (await queryDb(`SELECT userrange_id FROM UserSession LEFT JOIN User ON User.id=UserSession.user_id WHERE token like '${token}'`))[0];
    if (user.userrange_id == 4 || user.userrange_id == 3) { //if admin
        await queryDb(`UPDATE Resource SET classroom='${resourceData.aula}', capacity=${resourceData.capacidad} WHERE id=${resourceData.idrecurso}`);
        res.status(200).json({'message': 'Recurso modificado correctamente!'});
    }
    else {
        res.status(403).json({'message': 'Acceso denegado!'});
    }
});

app.post('/resources/delete', async (req, res) => {
    const resourceid = req.body.resourceid;
    const token = req.body.token;
    
    const user = (await queryDb(`SELECT userrange_id FROM UserSession LEFT JOIN User ON User.id=UserSession.user_id WHERE token like '${token}'`))[0];
    if (user.userrange_id == 4 || user.userrange_id == 3) { //if admin
        await queryDb(`DELETE FROM CourseResource WHERE resource_id=${resourceid}`);
        await queryDb(`DELETE FROM Resource WHERE id=${resourceid}`);
        res.status(200).json({'message': 'Recurso eliminado!'});
    }
    else {
        res.status(403).json({'message': 'Acceso denegado!'});
    }
});

app.post('/courses/resources/add', async (req, res) => {
    const courseid = req.body.courseid;
    const resourceid = req.body.resourceid;
    const token = req.body.token;
    
    const user = (await queryDb(`SELECT userrange_id FROM UserSession LEFT JOIN User ON User.id=UserSession.user_id WHERE token like '${token}'`))[0];
    if (user.userrange_id == 4 || user.userrange_id == 3) { //if admin
        await queryDb(`DELETE FROM CourseResource WHERE course_id=${courseid}`);
        await queryDb(`INSERT INTO CourseResource (course_id, resource_id) VALUES (${courseid}, ${resourceid})`);
        res.status(200).json({'message': 'Recurso asignado!'});
    }
    else {
        res.status(403).json({'message': 'Acceso denegado!'});
    }
});

app.post('/courses/resources/delete', async (req, res) => {
    const courseid = req.body.courseid;
    const token = req.body.token;
    
    const user = (await queryDb(`SELECT userrange_id FROM UserSession LEFT JOIN User ON User.id=UserSession.user_id WHERE token like '${token}'`))[0];
    if (user.userrange_id == 4 || user.userrange_id == 3) { //if admin
        await queryDb(`DELETE FROM CourseResource WHERE course_id=${courseid}`);
        res.status(200).json({'message': 'Recurso desasignado!'});
    }
    else {
        res.status(403).json({'message': 'Acceso denegado!'});
    }
});

app.post('/courses/delete', async (req, res) => {
    const courseid = req.body.courseid;
    const token = req.body.token;
    
    const user = (await queryDb(`SELECT userrange_id FROM UserSession LEFT JOIN User ON User.id=UserSession.user_id WHERE token like '${token}'`))[0];
    if (user.userrange_id == 4) { //if admin
        await queryDb(`DELETE FROM UserCourse WHERE course_id=${courseid}`);
        await queryDb(`DELETE FROM CourseResource WHERE course_id=${courseid}`);
        await queryDb(`DELETE FROM Course WHERE id=${courseid}`);
        res.status(200).json({'message': 'Curso eliminado!'});
    }
    else {
        res.status(403).json({'message': 'Acceso denegado!'});
    }
});

app.post('/courses/edit', async (req, res) => {
    const courseData = req.body;
    const token = req.body.token;
    
    const user = (await queryDb(`SELECT userrange_id FROM UserSession LEFT JOIN User ON User.id=UserSession.user_id WHERE token like '${token}'`))[0];
    if (user.userrange_id == 4 || user.userrange_id == 2) { // Check permissions
        const course = (await queryDb(`SELECT nombre, content, startDate, finishDate, ponente FROM Course WHERE id=${courseData.courseid}`))[0];

        let newName = courseData.nombre == ''  ? course.nombre : courseData.nombre;
        let newContent = courseData.contenido == ''  ? course.content : courseData.contenido;
        let newStartDate = courseData.fechaInicio == ''  ? course.startDate.toISOString().slice(0, 10) : courseData.fechaInicio;
        let newFinishDate = courseData.fechaFin == ''  ? course.finishDate.toISOString().slice(0, 10) : courseData.fechaFin;
        let newPonente = courseData.ponente == ''  ? course.ponente : courseData.ponente;

        await queryDb(`UPDATE Course SET nombre='${newName}', content='${newContent}', startDate='${newStartDate}', finishDate='${newFinishDate}', ponente='${newPonente}' WHERE id=${courseData.courseid}`);
        res.status(200).json({'message': 'Curso modificado!'});
    }
    else {
        res.status(403).json({'message': 'Acceso denegado!'});
    }
});

app.post('/courses/add', async (req, res) => {
    const courseData = req.body;
    const token = req.body.token;
    
    const user = (await queryDb(`SELECT userrange_id FROM UserSession LEFT JOIN User ON User.id=UserSession.user_id WHERE token like '${token}'`))[0];
    if (user.userrange_id == 4 || user.userrange_id == 2) { // Check permissions
        const insertResult = await queryDb(`INSERT INTO Course (nombre, content, startDate, finishDate, ponente) VALUES ('${courseData.nombre}', '${courseData.contenido}', '${courseData.fechaInicio}', '${courseData.fechaFin}', '${courseData.ponente}')`);
        if (insertResult.affectedRows > 0) {
            res.status(200).json({'message': 'Curso creado correctamente!'});
        }
        else {
            res.status(500).json({'message': 'Algo salio mal!'});
        }
    }
    else {
        res.status(403).json({'message': 'Acceso denegado!'});
    }
});

app.get('/courses', async (req, res) => {
    let course = await queryDb('SELECT * FROM Course');
    for (let i = 0; i < course.length; i++) {
        const matriculados = await queryDb(`SELECT User.username FROM UserCourse LEFT JOIN User ON User.id = UserCourse.user_id WHERE UserCourse.course_id=${course[i].id}`);
        course[i].matriculados = matriculados;
    }

    res.status(200).json(course);
});

app.post('/courses/enroll', async (req, res) => {
    const enrollData = req.body;
    const userData = (await queryDb(`SELECT id FROM User WHERE dni like '${enrollData.dni}'`))[0];
    const token = req.body.token;

    const reqUser = (await queryDb(`SELECT userrange_id, User.id, dni FROM UserSession LEFT JOIN User ON User.id=UserSession.user_id WHERE token like '${token}'`))[0];
    if (reqUser.userrange_id == 4 || userData.id == reqUser.id) {
        const enrollments = await queryDb(`SELECT * FROM UserCourse WHERE user_id=${userData.id} and course_id=${enrollData.courseid}`);
        if (enrollments.length > 0) {
            res.status(403).json({'message': 'Ya esta matriculado en ese curso!'});
        }
        else {
            const insertResult = await queryDb(`INSERT INTO UserCourse (user_id, course_id) VALUES (${userData.id}, ${enrollData.courseid})`);
            if (insertResult.affectedRows > 0) {
                res.status(200).json({'message': 'Inscrito correctamente!'});
            }
            else {
                res.status(500).json({'message': 'Algo salio mal!'});
            }
        }
    }
    else {
        res.status(403).json({'message': 'Acceso denegado!'});
    }

});

app.post('/courses/unenroll', async (req, res) => {
    const unenrollData = req.body;
    const userData = (await queryDb(`SELECT id FROM User WHERE dni like '${unenrollData.dni}'`))[0];
    const token = req.body.token;
    
    const reqUser = (await queryDb(`SELECT userrange_id, User.id, dni FROM UserSession LEFT JOIN User ON User.id=UserSession.user_id WHERE token like '${token}'`))[0];
    if (reqUser.userrange_id == 4 || userData.id == reqUser.id) {
        const enrollments = await queryDb(`SELECT * FROM UserCourse WHERE user_id=${userData.id} and course_id=${unenrollData.courseid}`);
        if (enrollments.length > 0) {
            const result = await queryDb(`DELETE FROM UserCourse WHERE course_id=${unenrollData.courseid} AND user_id=${userData.id}`)
            res.status(200).json({'message': 'Matriculacion anulada!'});
        }
        else {
            res.status(403).json({'message': 'No esta en ese curso!'});
        }
    }
    else {
        res.status(403).json({'message': 'Acceso denegado!'});
    }
    
});





//-------------------------------------------------------------------//
//                                                                   //
//                        SERVER & HELPERS                           //
//                                                                   //
//-------------------------------------------------------------------//


// Init express server
app.listen(process.env.APP_PORT, () => {
    console.log(`server running on port ${process.env.APP_PORT}`);
});


// Tries to login an user, on success returns the session token, on failure returns null
async function login(username, password) {
    const userData = (await queryDb(`SELECT * FROM User where username like '${username}'`))[0];
    const isCorrect = bcrypt.compareSync(password, userData.password);

    if (isCorrect) {
        await queryDb(`DELETE FROM UserSession WHERE user_id=${userData.id}`); // Close previous sessions
        const insertResult = await queryDb(`INSERT INTO UserSession (user_id, token, expire) VALUES (${userData.id}, UUID(), date_add(now(), interval 1 hour))`); // Creates a new session
        if (insertResult.affectedRows > 0) {
            const sessionToken = (await queryDb(`SELECT token FROM UserSession WHERE user_id=${userData.id}`))[0].token; // Gets the token from the new session
            return {
                username: userData.username,
                dni: userData.dni,
                userrange: userData.userrange_id,
                token: sessionToken
            };
        }
    }

    return null;
}

async function sessionExpired(token) {
    const sessionData = (await queryDb(`SELECT expire > NOW() as expired FROM UserSession WHERE token=${token}`))[0]; // Check if session expired
    if (sessionData.expired == 0) {
        await queryDb(`UPDATE UserSession SET expire=date_add(now(), interval 1 hour) WHERE token=${token}`); // Extend the session
        return false;
    }

    return true;
}

// Helper query function (temporal)
async function queryDb(query, params) {
    const connection = await mysql.createConnection({
        host: process.env.DB_HOST,
        user: process.env.DB_USER,
        password: process.env.DB_PASS,
        database: process.env.DB_DATABASE
    });
    
    const [results, ] = await connection.execute(query, params);

    return results;
}