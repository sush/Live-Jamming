-- MySQL dump 10.13  Distrib 5.1.37, for debian-linux-gnu (i486)
--
-- Host: localhost    Database: live-jamming_db
-- ------------------------------------------------------
-- Server version	5.1.37-1ubuntu5.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `countries`
--
USE `live-jamming_db`;
DROP TABLE IF EXISTS `countries`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `countries` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `country` varchar(50) COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=276 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `countries`
--

LOCK TABLES `countries` WRITE;
/*!40000 ALTER TABLE `countries` DISABLE KEYS */;
INSERT INTO `countries` VALUES (1,'Afghanistan'),(2,'Albania'),(3,'Algeria'),(4,'American Samoa'),(5,'Andorra'),(6,'Angola'),(7,'Anguilla'),(8,'Antarctica'),(9,'Antigua and Barbuda'),(10,'Argentina'),(11,'Armenia'),(12,'Aruba'),(13,'Ashmore and Cartier'),(14,'Australia'),(15,'Austria'),(16,'Azerbaijan'),(17,'The Bahamas'),(18,'Bahrain'),(19,'Baker Island'),(20,'Bangladesh'),(21,'Barbados'),(22,'Bassas da India'),(23,'Belarus'),(24,'Belgium'),(25,'Belize'),(26,'Benin'),(27,'Bermuda'),(28,'Bhutan'),(29,'Bolivia'),(30,'Bosnia and Herzegovina'),(31,'Botswana'),(32,'Bouvet Island'),(33,'Brazil'),(34,'British Indian Ocean Territory'),(35,'British Virgin Islands'),(36,'Brunei Darussalam'),(37,'Bulgaria'),(38,'Burkina Faso'),(39,'Burma'),(40,'Burundi'),(41,'Cambodia'),(42,'Cameroon'),(43,'Canada'),(44,'Cape Verde'),(45,'Cayman Islands'),(46,'Central African Republic'),(47,'Chad'),(48,'Chile'),(49,'China'),(50,'Christmas Island'),(51,'Clipperton Island'),(52,'Cocos (Keeling) Islands'),(53,'Colombia'),(54,'Comoros'),(55,'Congo, Democratic Republic of the'),(56,'Congo, Republic of the'),(57,'Cook Islands'),(58,'Coral Sea Islands'),(59,'Costa Rica'),(60,'Cote d\'Ivoire'),(61,'Croatia'),(62,'Cuba'),(63,'Cyprus'),(64,'Czech Republic'),(65,'Denmark'),(66,'Djibouti'),(67,'Dominica'),(68,'Dominican Republic'),(69,'East Timor'),(70,'Ecuador'),(71,'Egypt'),(72,'El Salvador'),(73,'Equatorial Guinea'),(74,'Eritrea'),(75,'Estonia'),(76,'Ethiopia'),(77,'Europa Island'),(78,'Falkland Islands (Islas Malvinas)'),(79,'Faroe Islands'),(80,'Fiji'),(81,'Finland'),(82,'France'),(83,'France, Metropolitan'),(84,'French Guiana'),(85,'French Polynesia'),(86,'French Southern and Antarctic Lands'),(87,'Gabon'),(88,'The Gambia'),(89,'Gaza Strip'),(90,'Georgia'),(91,'Germany'),(92,'Ghana'),(93,'Gibraltar'),(94,'Glorioso Islands'),(95,'Greece'),(96,'Greenland'),(97,'Grenada'),(98,'Guadeloupe'),(99,'Guam'),(100,'Guatemala'),(101,'Guernsey'),(102,'Guinea'),(103,'Guinea-Bissau'),(104,'Guyana'),(105,'Haiti'),(106,'Heard Island and McDonald Islands'),(107,'Holy See (Vatican City)'),(108,'Honduras'),(109,'Hong Kong (SAR)'),(110,'Howland Island'),(111,'Hungary'),(112,'Iceland'),(113,'India'),(114,'Indonesia'),(115,'Iran'),(116,'Iraq'),(117,'Ireland'),(118,'Israel'),(119,'Italy'),(120,'Jamaica'),(121,'Jan Mayen'),(122,'Japan'),(123,'Jarvis Island'),(124,'Jersey'),(125,'Johnston Atoll'),(126,'Jordan'),(127,'Juan de Nova Island'),(128,'Kazakhstan'),(129,'Kenya'),(130,'Kingman Reef'),(131,'Kiribati'),(132,'Korea, North'),(133,'Korea, South'),(134,'Kuwait'),(135,'Kyrgyzstan'),(136,'Laos'),(137,'Latvia'),(138,'Lebanon'),(139,'Lesotho'),(140,'Liberia'),(141,'Libya'),(142,'Liechtenstein'),(143,'Lithuania'),(144,'Luxembourg'),(145,'Macao'),(146,'Macedonia, The Former Yugoslav Republic of'),(147,'Madagascar'),(148,'Malawi'),(149,'Malaysia'),(150,'Maldives'),(151,'Mali'),(152,'Malta'),(153,'Man, Isle of'),(154,'Marshall Islands'),(155,'Martinique'),(156,'Mauritania'),(157,'Mauritius'),(158,'Mayotte'),(159,'Mexico'),(160,'Micronesia, Federated States of'),(161,'Midway Islands'),(162,'Miscellaneous (French)'),(163,'Moldova'),(164,'Monaco'),(165,'Mongolia'),(166,'Montenegro'),(167,'Montserrat'),(168,'Morocco'),(169,'Mozambique'),(170,'Myanmar'),(171,'Namibia'),(172,'Nauru'),(173,'Navassa Island'),(174,'Nepal'),(175,'Netherlands'),(176,'Netherlands Antilles'),(177,'New Caledonia'),(178,'New Zealand'),(179,'Nicaragua'),(180,'Niger'),(181,'Nigeria'),(182,'Niue'),(183,'Norfolk Island'),(184,'Northern Mariana Islands'),(185,'Norway'),(186,'Oman'),(187,'Pakistan'),(188,'Palau'),(189,'Palmyra Atoll'),(190,'Panama'),(191,'Papua New Guinea'),(192,'Paracel Islands'),(193,'Paraguay'),(194,'Peru'),(195,'Philippines'),(196,'Pitcairn Islands'),(197,'Poland'),(198,'Portugal'),(199,'Puerto Rico'),(200,'Qatar'),(201,'R'),(202,'Romania'),(203,'Russia'),(204,'Rwanda'),(205,'Saint Helena'),(206,'Saint Kitts and Nevis'),(207,'Saint Lucia'),(208,'Saint Pierre and Miquelon'),(209,'Saint Vincent and the Grenadines'),(210,'Samoa'),(211,'San Marino'),(212,'S'),(213,'Saudi Arabia'),(214,'Senegal'),(215,'Serbia'),(216,'Serbia and Montenegro'),(217,'Seychelles'),(218,'Sierra Leone'),(219,'Singapore'),(220,'Slovakia'),(221,'Slovenia'),(222,'Solomon Islands'),(223,'Somalia'),(224,'South Africa'),(225,'South Georgia and the South Sandwich Islands'),(226,'Spain'),(227,'Spratly Islands'),(228,'Sri Lanka'),(229,'Sudan'),(230,'Suriname'),(231,'Svalbard'),(232,'Swaziland'),(233,'Sweden'),(234,'Switzerland'),(235,'Syria'),(236,'Taiwan'),(237,'Tajikistan'),(238,'Tanzania'),(239,'Thailand'),(240,'Togo'),(241,'Tokelau'),(242,'Tonga'),(243,'Trinidad and Tobago'),(244,'Tromelin Island'),(245,'Tunisia'),(246,'Turkey'),(247,'Turkmenistan'),(248,'Turks and Caicos Islands'),(249,'Tuvalu'),(250,'Uganda'),(251,'Ukraine'),(252,'United Arab Emirates'),(253,'United Kingdom'),(254,'United States'),(255,'United States Minor Outlying Islands'),(256,'Uruguay'),(257,'Uzbekistan'),(258,'Vanuatu'),(259,'Venezuela'),(260,'Vietnam'),(261,'Virgin Islands'),(262,'Virgin Islands (UK)'),(263,'Virgin Islands (US)'),(264,'Wake Island'),(265,'Wallis and Futuna'),(266,'West Bank'),(267,'Western Sahara'),(268,'Western Samoa'),(269,'World'),(270,'Yemen'),(271,'Yugoslavia'),(272,'Zaire'),(273,'Zambia'),(274,'Zimbabwe'),(275,'Palestinian Territory, Occupied');
/*!40000 ALTER TABLE `countries` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2010-04-06 15:35:57
