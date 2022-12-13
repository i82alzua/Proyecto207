-- --------------------------------------------------------
-- Versión del servidor:         10.3.36-MariaDB-0+deb10u2 - Raspbian 10
-- SO del servidor:              debian-linux-gnueabihf
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;


-- Volcando estructura de base de datos para is2223
CREATE DATABASE IF NOT EXISTS `is2223` /*!40100 DEFAULT CHARACTER SET utf8mb4 */;
USE `is2223`;

-- Volcando estructura para tabla is2223.Course
CREATE TABLE IF NOT EXISTS `Course` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `nombre` varchar(50) DEFAULT NULL,
  `content` varchar(512) NOT NULL DEFAULT '',
  `startDate` date NOT NULL,
  `finishDate` date NOT NULL,
  `ponente` varchar(128) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4;

-- La exportación de datos fue deseleccionada.

-- Volcando estructura para tabla is2223.CourseResource
CREATE TABLE IF NOT EXISTS `CourseResource` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `course_id` int(10) unsigned NOT NULL,
  `resource_id` int(11) NOT NULL,
  `from` datetime DEFAULT NULL,
  `to` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_CourseResource_Course` (`course_id`),
  KEY `FK_CourseResource_Resource` (`resource_id`),
  CONSTRAINT `FK_CourseResource_Course` FOREIGN KEY (`course_id`) REFERENCES `Course` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `FK_CourseResource_Resource` FOREIGN KEY (`resource_id`) REFERENCES `Resource` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8mb4;

-- La exportación de datos fue deseleccionada.

-- Volcando estructura para tabla is2223.Resource
CREATE TABLE IF NOT EXISTS `Resource` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `classroom` varchar(50) NOT NULL,
  `capacity` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4;

-- La exportación de datos fue deseleccionada.

-- Volcando estructura para tabla is2223.User
CREATE TABLE IF NOT EXISTS `User` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(128) NOT NULL,
  `password` varchar(128) NOT NULL,
  `dni` varchar(9) DEFAULT '',
  `userrange_id` int(11) NOT NULL DEFAULT 1,
  PRIMARY KEY (`id`),
  KEY `FK_User_UserRange` (`userrange_id`),
  CONSTRAINT `FK_User_UserRange` FOREIGN KEY (`userrange_id`) REFERENCES `UserRange` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4;

-- La exportación de datos fue deseleccionada.

-- Volcando estructura para tabla is2223.UserCourse
CREATE TABLE IF NOT EXISTS `UserCourse` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL,
  `course_id` int(10) unsigned NOT NULL,
  `score` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  KEY `FK_UserCourse_User` (`user_id`),
  KEY `FK_UserCourse_Course` (`course_id`),
  CONSTRAINT `FK_UserCourse_Course` FOREIGN KEY (`course_id`) REFERENCES `Course` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `FK_UserCourse_User` FOREIGN KEY (`user_id`) REFERENCES `User` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8mb4;

-- La exportación de datos fue deseleccionada.

-- Volcando estructura para tabla is2223.UserRange
CREATE TABLE IF NOT EXISTS `UserRange` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `range` varchar(50) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4;

-- La exportación de datos fue deseleccionada.

-- Volcando estructura para tabla is2223.UserSession
CREATE TABLE IF NOT EXISTS `UserSession` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) unsigned NOT NULL,
  `token` varchar(128) NOT NULL,
  `expire` datetime NOT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_UserSession_User` (`user_id`),
  CONSTRAINT `FK_UserSession_User` FOREIGN KEY (`user_id`) REFERENCES `User` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=130 DEFAULT CHARSET=utf8mb4;

-- La exportación de datos fue deseleccionada.

-- Volcando estructura para vista is2223.v_CourseStats
-- Creando tabla temporal para superar errores de dependencia de VIEW
CREATE TABLE `v_CourseStats` (
	`id` INT(10) UNSIGNED NOT NULL,
	`passRate` DECIMAL(26,4) NOT NULL,
	`reachRate` DECIMAL(24,4) NULL
) ENGINE=MyISAM;

-- Volcando estructura para vista is2223.v_CourseStats
-- Eliminando tabla temporal y crear estructura final de VIEW
DROP TABLE IF EXISTS `v_CourseStats`;
CREATE ALGORITHM=UNDEFINED SQL SECURITY DEFINER VIEW `v_CourseStats` AS select `Course`.`id` AS `id`,ifnull(sum(if(`UserCourse`.`score` >= 5,1,0)) / count(`UserCourse`.`score`),0) AS `passRate`,count(`UserCourse`.`course_id`) / (select count(1) from `User`) AS `reachRate` from (`Course` left join `UserCourse` on(`UserCourse`.`course_id` = `Course`.`id`)) group by `Course`.`id`;

/*!40103 SET TIME_ZONE=IFNULL(@OLD_TIME_ZONE, 'system') */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
