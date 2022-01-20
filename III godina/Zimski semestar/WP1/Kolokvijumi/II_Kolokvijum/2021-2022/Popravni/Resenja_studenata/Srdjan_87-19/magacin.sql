-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Jan 19, 2022 at 09:52 PM
-- Server version: 5.7.31
-- PHP Version: 7.3.21

-- Podaci o rešenju
-- ----------------
-- Predmet: Web programiranje
-- Program: 2019
-- Školska godina: 2021-2022
-- Kolokvijum: II (popravni)
-- Autor: Srđan Todorović
    
-- Podaci o zadatku
-- ----------------
-- Predmet: Web programiranje
-- Školska godina: 2021-2022
-- Kolokvijum: II (popravni)

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `magacin`
--

-- --------------------------------------------------------

--
-- Table structure for table `korisnik`
--

DROP TABLE IF EXISTS `korisnik`;
CREATE TABLE IF NOT EXISTS `korisnik` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `korisnicko_ime` varchar(255) NOT NULL,
  `sifra` varchar(255) NOT NULL,
  `uloga` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `korisnik`
--

INSERT INTO `korisnik` (`id`, `korisnicko_ime`, `sifra`, `uloga`) VALUES
(1, 'pera_peric', 'pera_peric', 1),
(2, 'stefan_petrovic', 'stefan_petrovic', 2);

-- --------------------------------------------------------

--
-- Table structure for table `proizvod`
--

DROP TABLE IF EXISTS `proizvod`;
CREATE TABLE IF NOT EXISTS `proizvod` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `naziv` varchar(255) NOT NULL,
  `tip` varchar(255) NOT NULL,
  `opis` varchar(255) NOT NULL,
  `kolicina` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `proizvod`
--

INSERT INTO `proizvod` (`id`, `naziv`, `tip`, `opis`, `kolicina`) VALUES
(1, 'Nvidia GeForce RTX 3080 Ti', 'Graficka kartica', 'Kolicina memorije:12GB', 4),
(2, 'CORSAIR MP510', 'SSD', 'Kapacitet:960GB', 7),
(3, 'GIGABYTE X570S AORUS MASTER', 'Maticna ploca', 'AMD X570 | ATX | DDR4', 3);

-- --------------------------------------------------------

--
-- Table structure for table `tip_korisnika`
--

DROP TABLE IF EXISTS `tip_korisnika`;
CREATE TABLE IF NOT EXISTS `tip_korisnika` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `uloga` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `tip_korisnika`
--

INSERT INTO `tip_korisnika` (`id`, `uloga`) VALUES
(1, 'prodavac'),
(2, 'sef magacina');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
