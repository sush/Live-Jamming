DROP DATABASE IF EXISTS `live-jamming_db`;
CREATE DATABASE `live-jamming_db`;
USE `live-jamming_db`;

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';


-- -----------------------------------------------------
-- Table `record`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `record` ;

CREATE  TABLE IF NOT EXISTS `record` (
  `idrecord` INT NOT NULL ,
  `title` VARCHAR(45) NULL ,
  `date` DATETIME NULL ,
  `path` VARCHAR(45) NULL ,
  `duration` TIME NULL ,
  PRIMARY KEY (`idrecord`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;


-- -----------------------------------------------------
-- Table `countries`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `countries` ;

CREATE  TABLE IF NOT EXISTS `countries` (
  `idcountries` INT NOT NULL ,
  `wording` VARCHAR(45) NULL ,
  PRIMARY KEY (`idcountries`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;


-- -----------------------------------------------------
-- Table `level`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `level` ;

CREATE  TABLE IF NOT EXISTS `level` (
  `idlevel` INT NOT NULL ,
  `wording` VARCHAR(45) NULL ,
  PRIMARY KEY (`idlevel`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;


-- -----------------------------------------------------
-- Table `connection_type`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `connection_type` ;

CREATE  TABLE IF NOT EXISTS `connection_type` (
  `idconnection_type` INT NOT NULL ,
  `wording` VARCHAR(45) NULL ,
  PRIMARY KEY (`idconnection_type`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;


-- -----------------------------------------------------
-- Table `gender`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gender` ;

CREATE  TABLE IF NOT EXISTS `gender` (
  `idgender` INT NOT NULL ,
  `wording` VARCHAR(45) NULL ,
  PRIMARY KEY (`idgender`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;


-- -----------------------------------------------------
-- Table `user`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `users` ;

CREATE  TABLE IF NOT EXISTS `users` (
  `id` INT NOT NULL ,
  `login` VARCHAR(45) NULL ,
  `password` VARCHAR(45) NULL ,
  `email` VARCHAR(45) NULL ,
  `connected` TINYINT(1)  NULL ,
  `description` VARCHAR(45) NULL ,
  `town` VARCHAR(45) NULL ,
  `idcountries` INT NOT NULL ,
  `idlevel` INT NOT NULL ,
  `idconnection_type` INT NOT NULL ,
  `idgender` INT NOT NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_user_countries` (`idcountries` ASC) ,
  INDEX `fk_user_level` (`idlevel` ASC) ,
  INDEX `fk_user_connection_type` (`idconnection_type` ASC) ,
  INDEX `fk_user_gender` (`idgender` ASC) ,
  CONSTRAINT `fk_user_countries`
    FOREIGN KEY (`idcountries` )
    REFERENCES `countries` (`idcountries` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_user_level`
    FOREIGN KEY (`idlevel` )
    REFERENCES `level` (`idlevel` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_user_connection_type`
    FOREIGN KEY (`idconnection_type` )
    REFERENCES `connection_type` (`idconnection_type` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_user_gender`
    FOREIGN KEY (`idgender` )
    REFERENCES `gender` (`idgender` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;


-- -----------------------------------------------------
-- Table `record_participant`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `record_participant` ;

CREATE  TABLE IF NOT EXISTS `record_participant` (
  `idrecord` INT NOT NULL ,
  `iduser` INT NOT NULL ,
  INDEX `fk_record_participant_record1` (`idrecord` ASC) ,
  INDEX `fk_record_participant_user1` (`iduser` ASC) ,
  CONSTRAINT `fk_record_participant_record1`
    FOREIGN KEY (`idrecord` )
    REFERENCES `record` (`idrecord` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_record_participant_user1`
    FOREIGN KEY (`iduser` )
    REFERENCES `user` (`iduser` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;


-- -----------------------------------------------------
-- Table `contact`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `contact` ;

CREATE  TABLE IF NOT EXISTS `contact` (
  `iduser` INT NOT NULL ,
  `idcontact` INT NOT NULL ,
  INDEX `fk_contact_user` (`iduser` ASC) ,
  INDEX `fk_contact_user1` (`idcontact` ASC) ,
  CONSTRAINT `fk_contact_user`
    FOREIGN KEY (`iduser` )
    REFERENCES `user` (`iduser` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_contact_user1`
    FOREIGN KEY (`idcontact` )
    REFERENCES `user` (`iduser` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
