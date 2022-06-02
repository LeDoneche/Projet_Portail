-- phpMyAdmin SQL Dump
-- version 4.6.6deb5
-- https://www.phpmyadmin.net/
--
-- Client :  localhost:3306
-- Généré le :  Jeu 02 Juin 2022 à 09:08
-- Version du serveur :  10.3.34-MariaDB-0+deb10u1
-- Version de PHP :  7.3.31-1~deb10u1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données :  `Portail`
--

-- --------------------------------------------------------

--
-- Structure de la table `Parking`
--

CREATE TABLE `Parking` (
  `NbPlace` int(2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Contenu de la table `Parking`
--

INSERT INTO `Parking` (`NbPlace`) VALUES
(15);

-- --------------------------------------------------------

--
-- Structure de la table `Personnel`
--

CREATE TABLE `Personnel` (
  `nom` varchar(20) NOT NULL,
  `prenom` varchar(20) NOT NULL,
  `QR` varchar(8) NOT NULL,
  `adresse_mail` varchar(40) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Contenu de la table `Personnel`
--

INSERT INTO `Personnel` (`nom`, `prenom`, `QR`, `adresse_mail`) VALUES
('gomez', 'mel', '4ed8bacd', 'mel.gomez17@gmail.com'),
('jehanno', 'erwan', '89904398', 'jehanno21@gmail.com');

--
-- Index pour les tables exportées
--

--
-- Index pour la table `Personnel`
--
ALTER TABLE `Personnel`
  ADD PRIMARY KEY (`QR`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
