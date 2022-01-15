-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Jan 15, 2022 at 01:15 PM
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
--    Školska godina: 2020-2021
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
-- Database: `oebs`
--

-- --------------------------------------------------------

--
-- Table structure for table `countries`
--

DROP TABLE IF EXISTS `countries`;
CREATE TABLE IF NOT EXISTS `countries` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `continent` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `countries`
--

INSERT INTO `countries` (`id`, `name`, `continent`) VALUES
(1, 'USA', 'North America'),
(2, 'Russia', 'Europe and Asia');

-- --------------------------------------------------------

--
-- Table structure for table `topiccou`
--

DROP TABLE IF EXISTS `topiccou`;
CREATE TABLE IF NOT EXISTS `topiccou` (
  `topicID` int(11) NOT NULL,
  `countryID` int(11) NOT NULL,
  `statement` varchar(1000) NOT NULL,
  PRIMARY KEY (`topicID`,`countryID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `topiccou`
--

INSERT INTO `topiccou` (`topicID`, `countryID`, `statement`) VALUES
(1, 1, 'Srbija je ostvarila vidan napredak na polju informacionih tehnologija'),
(1, 2, 'Rusija je napravila telefon sa 2 ekrana. Buducnost i Srbija imaju neraskidive veze'),
(2, 2, 'Zajednicka borba je prioritet za prosperitet i ocuvanje mira');

-- --------------------------------------------------------

--
-- Table structure for table `topics`
--

DROP TABLE IF EXISTS `topics`;
CREATE TABLE IF NOT EXISTS `topics` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `topic` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `topics`
--

INSERT INTO `topics` (`id`, `topic`) VALUES
(1, 'Information technologies'),
(2, 'Terorrism');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
