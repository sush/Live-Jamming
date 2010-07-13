use "live-jamming_db";

DROP TABLE IF EXISTS friends;
CREATE TABLE friends
       (id int,
       friend_id int,
       PRIMARY KEY (id, friend_id),
       FOREIGN KEY (id)
       	       REFERENCES users (id)
	       ON UPDATE CASCADE
	       ON DELETE CASCADE,
       FOREIGN KEY (friend_id)
       	       REFERENCES users (id)
	       ON UPDATE CASCADE
	       ON DELETE CASCADE)
       ENGINE=INNODB;

INSERT INTO friends
       VALUES (16,27), (16,17), (16,23);








DROP FUNCTION  IF EXISTS i18n_get;
DROP PROCEDURE IF EXISTS PROC_GET_USERINFO;
DROP PROCEDURE IF EXISTS PROC_GET_USERINFO_LOGIN;
DROP PROCEDURE IF EXISTS PROC_GET_FRIENDLIST;
DROP PROCEDURE IF EXISTS PROC_GET_FRIENDLIST_LOGIN;
DROP PROCEDURE IF EXISTS PROC_ADD_FRIEND;
DROP PROCEDURE IF EXISTS PROC_ADD_FRIEND_LOGIN;

delimiter //

CREATE FUNCTION i18n_get(fk int, m varchar(50), l varchar(50))
	RETURNS VARCHAR(50)
BEGIN
	DECLARE ret varchar(50);

	SELECT content INTO ret from i18n where foreign_key=fk and model=m and locale=l;

	RETURN(ret);
END//

CREATE PROCEDURE PROC_GET_USERINFO (IN _user_id INT, IN _locale VARCHAR(50))
BEGIN
	SELECT users.id, login,
		i18n_get(gender_id, "Gender", "fre") gender,
		city, country,
		i18n_get(instrument_id,"Instrument","fre") instrument,
		i18n_get(users.level_id,"Level","fre") level
	FROM users
		LEFT JOIN countries on(users.country_id=countries.id)
		LEFT JOIN cities on (users.city_id = cities.id)
	WHERE users.id=_user_id;
END//

CREATE PROCEDURE PROC_GET_USERINFO_LOGIN (IN _user_login VARCHAR(50), IN _locale VARCHAR(50))
BEGIN
	CALL PROC_GET_USERINFO((SELECT id from users WHERE login=_user_login), _locale);
END//

CREATE PROCEDURE PROC_GET_FRIENDLIST (IN _user_id INT)
BEGIN
	SELECT login 
	FROM friends
	LEFT JOIN users ON (users.id = friend_id)
	WHERE friends.id=_user_id;
END//

CREATE PROCEDURE PROC_GET_FRIENDLIST_LOGIN (IN _user_login VARCHAR(50))
BEGIN
	CALL PROC_GET_FRIENDLIST((SELECT id FROM users WHERE login=_user_login));
END//

CREATE PROCEDURE PROC_ADD_FRIEND_LOGIN (IN _user_login VARCHAR(50), IN _friend_login VARCHAR(50))
BEGIN
	INSERT INTO friends
	        values((SELECT id from users where login=_user_login), (select id from users where login=_friend_login));
	SELECT users.id from  users
	LEFT OUTER JOIN friends ON (users.id = friends.friend_id)
	       WHERE friends.id= (select id from users where login=_user_login) and users.login=_friend_login;
END//

CREATE PROCEDURE PROC_ADD_FRIEND (IN _user_id INT, IN _friend_id INT)
BEGIN
	INSERT INTO friends
	        values(_user_id, _friend_id);
	SELECT id from  users
	       WHERE friends.id=_user_id and friends.friend_id=_friend_id;
END//