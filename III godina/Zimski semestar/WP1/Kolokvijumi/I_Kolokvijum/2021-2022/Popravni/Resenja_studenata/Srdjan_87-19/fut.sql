-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Jan 19, 2022 at 06:46 PM
-- Server version: 5.7.31
-- PHP Version: 7.3.21

-- Podaci o rešenju
-- ----------------
-- Predmet: Web programiranje
-- Program: 2019
-- Školska godina: 2021-2022
-- Kolokvijum: I (popravni)
-- Autor: Srđan Todorović
    
-- Podaci o zadatku
-- ----------------
-- Predmet: Web programiranje
-- Školska godina: 2021-2022
-- Kolokvijum: I (popravni)


SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `fut`
--

-- --------------------------------------------------------

--
-- Table structure for table `buffs`
--

DROP TABLE IF EXISTS `buffs`;
CREATE TABLE IF NOT EXISTS `buffs` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `rating_buff` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `buffs`
--

INSERT INTO `buffs` (`id`, `name`, `rating_buff`) VALUES
(1, 'buff', 1),
(2, 'strong buff', 2),
(3, 'very strong buff', 4);

-- --------------------------------------------------------

--
-- Table structure for table `players`
--

DROP TABLE IF EXISTS `players`;
CREATE TABLE IF NOT EXISTS `players` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `position` varchar(255) NOT NULL,
  `rating` int(11) NOT NULL,
  `team_id` int(11) DEFAULT NULL,
  `buff_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `players`
--

INSERT INTO `players` (`id`, `name`, `position`, `rating`, `team_id`, `buff_id`) VALUES
(1, 'player 1', 'forward', 84, 1, NULL),
(2, 'player 2', 'back', 86, 1, 2),
(3, 'player 3', 'center', 92, 1, 3),
(4, 'player A', 'front', 94, 2, 1),
(5, 'player B', 'center', 80, 2, NULL),
(6, 'player 4', 'back', 84, NULL, 2);

-- --------------------------------------------------------

--
-- Table structure for table `teams`
--

DROP TABLE IF EXISTS `teams`;
CREATE TABLE IF NOT EXISTS `teams` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `team_name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `teams`
--

INSERT INTO `teams` (`id`, `team_name`) VALUES
(1, 'Primary Team'),
(2, 'Secondary Team'),
(3, 'Random Team');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
