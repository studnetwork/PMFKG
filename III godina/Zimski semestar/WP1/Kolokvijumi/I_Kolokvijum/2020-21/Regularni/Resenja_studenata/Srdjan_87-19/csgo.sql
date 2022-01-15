-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Jan 15, 2022 at 01:14 PM
-- Server version: 5.7.31
-- PHP Version: 7.3.21

-- --------------------------------------------------------
--    Podaci o rešenju
--    ----------------
--    Predmet: Web programiranje
--    Program: 2019
--    Školska godina: 2021-2022
--    Kolokvijum: I
--    Autor: Srđan Todorović
--    
--    Podaci o zadatku
--    ----------------
--    Predmet: Web programiranje
--    Školska godina: 2015-2016
--    Kolokvijum: I
-- --------------------------------------------------------


SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `csgo`
--

-- --------------------------------------------------------

--
-- Table structure for table `loadout`
--

DROP TABLE IF EXISTS `loadout`;
CREATE TABLE IF NOT EXISTS `loadout` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `userID` int(11) NOT NULL,
  `weaponID` int(11) NOT NULL,
  `t_ct` tinyint(1) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=0 DEFAULT CHARSET=utf8;


-- --------------------------------------------------------

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
CREATE TABLE IF NOT EXISTS `user` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(255) NOT NULL,
  `money` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`id`, `username`, `money`) VALUES
(1, 's1mple', 12000),
(2, 'dev1ce', 7600),
(3, 'olofmeister', 9850),
(4, 'kennyS', 6700);

-- --------------------------------------------------------

--
-- Table structure for table `weapon`
--

DROP TABLE IF EXISTS `weapon`;
CREATE TABLE IF NOT EXISTS `weapon` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `price` int(11) NOT NULL,
  `ct` tinyint(1) NOT NULL,
  `t` tinyint(1) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `weapon`
--

INSERT INTO `weapon` (`id`, `name`, `price`, `ct`, `t`) VALUES
(1, 'M4A1', 3100, 1, 1),
(2, 'M4A1-S', 3100, 1, 0),
(3, 'Desert Deagle', 700, 1, 1),
(4, 'AWP ', 4750, 1, 1),
(5, 'Famas', 2050, 1, 0),
(6, 'AUG', 3300, 1, 0),
(7, 'MP9', 1250, 0, 1),
(8, 'Sawed-Off', 1100, 0, 1),
(9, 'Negev', 1700, 1, 1);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
