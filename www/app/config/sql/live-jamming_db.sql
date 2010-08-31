DROP DATABASE IF EXISTS `live-jamming_db`;
CREATE DATABASE `live-jamming_db`;
USE `live-jamming_db`;

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';


-- -----------------------------------------------------
-- Table `records`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `records` ;

CREATE  TABLE IF NOT EXISTS `records` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `title` VARCHAR(256) NULL ,
  `date` DATETIME NULL ,
  `path` VARCHAR(256) NULL ,
  `duration` TIME NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;


-- -----------------------------------------------------
-- Table `countries`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `countries` ;

CREATE  TABLE IF NOT EXISTS `countries` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `wording` VARCHAR(256) NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;


-- -----------------------------------------------------
-- Table `levels`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `levels` ;

CREATE  TABLE IF NOT EXISTS `levels` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `wording` VARCHAR(256) NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;


-- -----------------------------------------------------
-- Table `connection_types`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `connection_types` ;

CREATE  TABLE IF NOT EXISTS `connection_types` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `wording` VARCHAR(256) NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;


-- -----------------------------------------------------
-- Table `genders`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `genders` ;

CREATE  TABLE IF NOT EXISTS `genders` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `wording` VARCHAR(256) NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;


-- -----------------------------------------------------
-- Table `users`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `users` ;

CREATE  TABLE IF NOT EXISTS `users` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `login` VARCHAR(256) NULL ,
  `password` VARCHAR(256) NULL ,
  `email` VARCHAR(256) NULL ,
  `connected` TINYINT(1)  NULL ,
  `description` TEXT NULL ,
  `city` VARCHAR(256) NULL ,
  `country_id` INT NULL ,
  `level_id` INT NULL ,
  `connection_type_id` INT NULL ,
  `gender_id` INT NULL ,
  `created` DATETIME NULL,
  `modified` DATETIME NULL,
  PRIMARY KEY (`id`) ,
  INDEX `fk_user_countries` (`country_id` ASC) ,
  INDEX `fk_user_level` (`level_id` ASC) ,
  INDEX `fk_user_connection_type` (`connection_type_id` ASC) ,
  INDEX `fk_user_gender` (`gender_id` ASC) ,
  CONSTRAINT `fk_user_countries`
    FOREIGN KEY (`country_id` )
    REFERENCES `countries` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_user_level`
    FOREIGN KEY (`level_id` )
    REFERENCES `levels` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_user_connection_type`
    FOREIGN KEY (`connection_type_id` )
    REFERENCES `connection_types` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_user_gender`
    FOREIGN KEY (`gender_id` )
    REFERENCES `genders` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;


-- -----------------------------------------------------
-- Table `record_participants`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `record_participants` ;

CREATE  TABLE IF NOT EXISTS `record_participants` (
  `record_id` INT NOT NULL ,
  `user_id` INT NOT NULL ,
  INDEX `fk_record_participant_record1` (`record_id` ASC) ,
  INDEX `fk_record_participant_user1` (`user_id` ASC) ,
  CONSTRAINT `fk_record_participant_record1`
    FOREIGN KEY (`record_id` )
    REFERENCES `records` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_record_participant_user1`
    FOREIGN KEY (`user_id` )
    REFERENCES `users` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;


-- -----------------------------------------------------
-- Table `contacts`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `contacts` ;

CREATE  TABLE IF NOT EXISTS `contacts` (
  `user_id` INT NOT NULL ,
  `contact_id` INT NOT NULL ,
  INDEX `fk_contact_user` (`user_id` ASC) ,
  INDEX `fk_contact_user1` (`contact_id` ASC) ,
  CONSTRAINT `fk_contact_user`
    FOREIGN KEY (`user_id` )
    REFERENCES `users` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_contact_user1`
    FOREIGN KEY (`contact_id` )
    REFERENCES `users` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
