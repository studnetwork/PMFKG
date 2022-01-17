-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Jan 17, 2022 at 08:01 AM
-- Server version: 5.7.31
-- PHP Version: 7.3.21

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `vaterpolo`
--

-- --------------------------------------------------------

--
-- Table structure for table `grupa`
--

DROP TABLE IF EXISTS `grupa`;
CREATE TABLE IF NOT EXISTS `grupa` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(256) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `grupa`
--

INSERT INTO `grupa` (`id`, `name`) VALUES
(1, 'Grupa A'),
(2, 'Grupa B'),
(3, 'Grupa C'),
(4, 'Grupa D');

-- --------------------------------------------------------

--
-- Table structure for table `igraci`
--

DROP TABLE IF EXISTS `igraci`;
CREATE TABLE IF NOT EXISTS `igraci` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `ime` varchar(256) NOT NULL,
  `tim_id` int(11) NOT NULL,
  `biografija` varchar(400) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=14 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `igraci`
--

INSERT INTO `igraci` (`id`, `ime`, `tim_id`, `biografija`) VALUES
(1, 'Dusan Mandic', 2, 'Najbolji igrac; prva nagrada'),
(2, 'Zivko Gogic', 2, ''),
(3, 'Filip Filipovic', 2, 'Fusce dignissim felis et condimentum gravida. Etiam eget tincidunt arcu, vitae volutpat nunc. Aenean sed magna commodo, commodo sem at, tristique velit. Ut pulvinar ultrices elementum. '),
(4, 'Viktor Raskovic', 2, ''),
(5, 'Martin Papez', 4, 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent suscipit faucibus enim, non semper turpis rutrum sed. Ut aliquet suscipit metus sit amet consequat. Suspendisse quis vestibulum urna. '),
(6, 'Luka Bajic', 4, ''),
(10, 'Viktor Nagy', 6, 'Vestibulum id eleifend metus. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. '),
(11, 'Daniel Angyal', 6, ''),
(12, 'Tiberiu Negrean', 5, 'Morbi sed aliquam elit. Etiam eget sagittis ex. Nunc laoreet dui sapien, eu mattis sapien ornare et. '),
(13, 'Marius Tic', 5, '');

-- --------------------------------------------------------

--
-- Table structure for table `timovi`
--

DROP TABLE IF EXISTS `timovi`;
CREATE TABLE IF NOT EXISTS `timovi` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `ime` varchar(256) NOT NULL,
  `grupa_id` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `timovi`
--

INSERT INTO `timovi` (`id`, `ime`, `grupa_id`) VALUES
(1, 'Francuska', 2),
(2, 'Srbija', 2),
(3, 'Malta', 2),
(4, 'Hrvatska', 2),
(5, 'Rumunija', 1),
(6, 'Madjarska', 1);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
