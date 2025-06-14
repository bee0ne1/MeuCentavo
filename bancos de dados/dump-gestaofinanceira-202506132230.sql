/*M!999999\- enable the sandbox mode */ 
-- MariaDB dump 10.19-11.8.2-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: gestaofinanceira
-- ------------------------------------------------------
-- Server version	11.8.2-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*M!100616 SET @OLD_NOTE_VERBOSITY=@@NOTE_VERBOSITY, NOTE_VERBOSITY=0 */;

--
-- Table structure for table `cliente`
--

DROP TABLE IF EXISTS `cliente`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `cliente` (
  `cli_id` int(11) NOT NULL AUTO_INCREMENT,
  `cli_cpf` varchar(25) NOT NULL,
  `cli_nome` varchar(100) NOT NULL,
  `cli_dataCadastro` datetime DEFAULT NULL,
  `cli_cep` varchar(12) DEFAULT NULL,
  `cli_endereco` varchar(100) DEFAULT NULL,
  `cli_numero` int(11) DEFAULT NULL,
  `cli_complemento` varchar(70) DEFAULT NULL,
  `cli_bairro` varchar(70) DEFAULT NULL,
  `cli_cidade` varchar(70) DEFAULT NULL,
  `cli_estado` varchar(50) DEFAULT NULL,
  `cli_email` varchar(150) DEFAULT NULL,
  `cli_celular` varchar(150) NOT NULL,
  `cli_observacao` text DEFAULT NULL,
  PRIMARY KEY (`cli_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cliente`
--

LOCK TABLES `cliente` WRITE;
/*!40000 ALTER TABLE `cliente` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `cliente` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `contapagar`
--

DROP TABLE IF EXISTS `contapagar`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `contapagar` (
  `pag_id` int(11) NOT NULL AUTO_INCREMENT,
  `pag_numDoc` int(11) NOT NULL,
  `pag_dataDoc` datetime NOT NULL,
  `pag_descDoc` varchar(150) NOT NULL,
  `cli_id` int(11) NOT NULL,
  `emp_id` int(11) NOT NULL,
  `pag_formaPag` varchar(50) NOT NULL,
  `pag_valorPrincipal` decimal(10,2) DEFAULT NULL,
  `pag_valorJuros` decimal(10,2) DEFAULT NULL,
  `pag_valorMulta` decimal(10,2) DEFAULT NULL,
  `pag_valorTotal` decimal(10,2) DEFAULT NULL,
  PRIMARY KEY (`pag_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `contapagar`
--

LOCK TABLES `contapagar` WRITE;
/*!40000 ALTER TABLE `contapagar` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `contapagar` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `contareceber`
--

DROP TABLE IF EXISTS `contareceber`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `contareceber` (
  `rec_id` int(11) NOT NULL AUTO_INCREMENT,
  `rec_numDoc` int(11) NOT NULL,
  `rec_dataDoc` datetime NOT NULL,
  `rec_descDoc` varchar(150) DEFAULT NULL,
  `cli_id` int(11) NOT NULL,
  `emp_id` int(11) NOT NULL,
  `rec_formaPagto` varchar(50) NOT NULL,
  `rec_valorPrincipal` decimal(10,2) DEFAULT NULL,
  `rec_valorJuros` decimal(10,2) DEFAULT NULL,
  `rec_valorMulta` decimal(10,2) DEFAULT NULL,
  `rec_valorTotal` decimal(10,2) DEFAULT NULL,
  PRIMARY KEY (`rec_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `contareceber`
--

LOCK TABLES `contareceber` WRITE;
/*!40000 ALTER TABLE `contareceber` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `contareceber` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `empresa`
--

DROP TABLE IF EXISTS `empresa`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `empresa` (
  `emp_id` int(11) NOT NULL AUTO_INCREMENT,
  `emp_cnpj` varchar(35) NOT NULL,
  `emp_razao` varchar(200) NOT NULL,
  `emp_dataCadastro` datetime NOT NULL,
  `emp_cep` varchar(12) NOT NULL,
  `emp_endereco` varchar(100) NOT NULL,
  `emp_numero` int(11) NOT NULL,
  `emp_complemento` varchar(70) DEFAULT NULL,
  `emp_bairro` varchar(70) DEFAULT NULL,
  `emp_cidade` varchar(50) DEFAULT NULL,
  `emp_estado` varchar(50) DEFAULT NULL,
  `emp_email` varchar(50) DEFAULT NULL,
  `emp_fonefixo` varchar(15) DEFAULT NULL,
  `emp_fonecelular` varchar(15) DEFAULT NULL,
  `emp_observacao` text DEFAULT NULL,
  PRIMARY KEY (`emp_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `empresa`
--

LOCK TABLES `empresa` WRITE;
/*!40000 ALTER TABLE `empresa` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `empresa` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `formapagto`
--

DROP TABLE IF EXISTS `formapagto`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `formapagto` (
  `forma_id` int(11) NOT NULL AUTO_INCREMENT,
  `forma_descricao` varchar(150) NOT NULL,
  PRIMARY KEY (`forma_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `formapagto`
--

LOCK TABLES `formapagto` WRITE;
/*!40000 ALTER TABLE `formapagto` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `formapagto` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `usuario`
--

DROP TABLE IF EXISTS `usuario`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `usuario` (
  `user_id` int(11) NOT NULL AUTO_INCREMENT,
  `user_usuario` varchar(50) NOT NULL,
  `user_password` varchar(50) NOT NULL,
  PRIMARY KEY (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `usuario`
--

LOCK TABLES `usuario` WRITE;
/*!40000 ALTER TABLE `usuario` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `usuario` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Dumping routines for database 'gestaofinanceira'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*M!100616 SET NOTE_VERBOSITY=@OLD_NOTE_VERBOSITY */;

-- Dump completed on 2025-06-13 22:30:45
