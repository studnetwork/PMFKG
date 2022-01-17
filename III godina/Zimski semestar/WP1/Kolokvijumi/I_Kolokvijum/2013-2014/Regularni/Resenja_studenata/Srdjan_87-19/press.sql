-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Jan 17, 2022 at 07:52 AM
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
-- Database: `press`
--

-- --------------------------------------------------------

--
-- Table structure for table `ckomentari`
--

DROP TABLE IF EXISTS `ckomentari`;
CREATE TABLE IF NOT EXISTS `ckomentari` (
  `comm_id` int(11) NOT NULL AUTO_INCREMENT,
  `vest_id` int(11) NOT NULL,
  `tekst` varchar(255) NOT NULL,
  PRIMARY KEY (`comm_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ckomentari`
--

INSERT INTO `ckomentari` (`comm_id`, `vest_id`, `tekst`) VALUES
(13, 3, 'novi komentar');

-- --------------------------------------------------------

--
-- Table structure for table `komentari`
--

DROP TABLE IF EXISTS `komentari`;
CREATE TABLE IF NOT EXISTS `komentari` (
  `komentar_id` int(11) NOT NULL AUTO_INCREMENT,
  `vest_id` int(11) NOT NULL,
  `tekst` varchar(255) NOT NULL,
  `pozitivno` tinyint(1) NOT NULL,
  `negativno` tinyint(1) NOT NULL,
  PRIMARY KEY (`komentar_id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `komentari`
--

INSERT INTO `komentari` (`komentar_id`, `vest_id`, `tekst`, `pozitivno`, `negativno`) VALUES
(7, 2, 'Bravo devojke! To se od vas i ocekivalo. Nemacki oktopod je to i predvideo :)', 0, 0),
(8, 2, 'Svaka cast! Samo da ne izgore od zelje kao Marko Pantelic i na kraju nista...', 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `vesti`
--

DROP TABLE IF EXISTS `vesti`;
CREATE TABLE IF NOT EXISTS `vesti` (
  `vest_id` int(11) NOT NULL AUTO_INCREMENT,
  `naslov` varchar(255) NOT NULL,
  `opis` varchar(255) NOT NULL,
  PRIMARY KEY (`vest_id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `vesti`
--

INSERT INTO `vesti` (`vest_id`, `naslov`, `opis`) VALUES
(1, 'Fudbaleri u Montevideou', 'U januaru mesecu nastavak price o jugoslovenskoj fudbalskoj reprezentaciji i ostatak teksta koji se nece prikazati'),
(2, 'Rukometasice pobedile Norvesku', 'Norveska na kolenima! Malo ko je ockivao zavrsnicu utamice u kojoj su nase devojke pruzile najbolju partiju na turniru.'),
(3, 'Da li rukometasice mogu do zlate medalje?', 'Marko Pantelic, fudbalska legenda sa impozantnom cifrom od 5 postignutih golova i ostatak teksta koji se ne prikazuje');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
