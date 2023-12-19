-- phpMyAdmin SQL Dump
-- version 4.7.9
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jul 02, 2021 at 06:55 PM
-- Server version: 10.1.31-MariaDB
-- PHP Version: 7.2.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `medicaredb`
--

-- --------------------------------------------------------

--
-- Table structure for table `medicines`
--

CREATE TABLE `medicines` (
  `medicineId` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `type` varchar(255) NOT NULL,
  `medicalCondition` varchar(255) NOT NULL,
  `expiryDate` date NOT NULL,
  `meansTotake` varchar(255) NOT NULL,
  `image` varchar(255) NOT NULL,
  `importance` varchar(255) DEFAULT NULL,
  `createdDate` datetime NOT NULL,
  `updateDate` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `medicines`
--

INSERT INTO `medicines` (`medicineId`, `name`, `type`, `medicalCondition`, `expiryDate`, `meansTotake`, `image`, `importance`, `createdDate`, `updateDate`) VALUES
(1, 'filestmedicine', 'anupam', 'Heart attack', '2021-06-17', 'tablet', '806117.jpg', 'testingg                                                    ', '2021-06-29 05:43:03', '2021-06-29 21:13:03'),
(3, 'mma', 'anupam', 'Heart attack', '2021-06-20', 'tablet', '1625068519_xS8XdX6.jpg', 'nn', '2021-06-30 05:55:19', '2021-06-30 21:25:19');

-- --------------------------------------------------------

--
-- Table structure for table `medicine_schedule`
--

CREATE TABLE `medicine_schedule` (
  `scheduleId` int(11) NOT NULL,
  `medicineId` int(11) NOT NULL,
  `day` varchar(255) NOT NULL,
  `medTime` time NOT NULL,
  `createdDate` datetime NOT NULL,
  `updateDate` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `medicine_schedule`
--

INSERT INTO `medicine_schedule` (`scheduleId`, `medicineId`, `day`, `medTime`, `createdDate`, `updateDate`) VALUES
(1, 1, 'Monday', '12:30:00', '2021-06-29 05:43:03', '2021-06-29 21:13:04'),
(3, 3, 'Monday', '12:30:00', '2021-06-30 05:55:19', '2021-06-30 21:25:19');

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE `user` (
  `userId` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `username` varchar(255) NOT NULL,
  `email` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `gender` enum('Male','Female','Other') NOT NULL DEFAULT 'Male',
  `age` varchar(255) NOT NULL,
  `medicalCondition` varchar(255) NOT NULL,
  `doctorContact` varchar(255) NOT NULL,
  `status` enum('Active','Inactive') NOT NULL DEFAULT 'Active',
  `createdDate` datetime NOT NULL,
  `updateDate` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`userId`, `name`, `username`, `email`, `password`, `gender`, `age`, `medicalCondition`, `doctorContact`, `status`, `createdDate`, `updateDate`) VALUES
(1, 'sonal', 'root', 'sonal@gmail.com', 'testing123', 'Male', '44', 'Heart attack', '87359743', 'Active', '2021-06-27 00:00:00', '2021-06-27 12:49:37'),
(2, 'anupam', 'sonalwisdom', 'anupam@123.com', 'glow@123', 'Male', '20', 'nil', 'nil', 'Active', '2021-06-27 00:00:00', '2021-06-27 16:11:42');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `medicines`
--
ALTER TABLE `medicines`
  ADD PRIMARY KEY (`medicineId`);

--
-- Indexes for table `medicine_schedule`
--
ALTER TABLE `medicine_schedule`
  ADD PRIMARY KEY (`scheduleId`);

--
-- Indexes for table `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`userId`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `medicines`
--
ALTER TABLE `medicines`
  MODIFY `medicineId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `medicine_schedule`
--
ALTER TABLE `medicine_schedule`
  MODIFY `scheduleId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `user`
--
ALTER TABLE `user`
  MODIFY `userId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
