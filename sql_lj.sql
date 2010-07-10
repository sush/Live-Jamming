

use "live-jamming_db";
DROP FUNCTION IF EXISTS i18n_get;
DROP PROCEDURE IF EXISTS PROC_GET_USERINFO;
DROP PROCEDURE IF EXISTS PROC_GET_USERINFO_LOGIN;

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
		i18n_get(users.level_id,"Level","fre") levela
	FROM users
		LEFT JOIN countries on(users.country_id=countries.id)
		LEFT JOIN cities on (users.city_id = cities.id)
	WHERE users.id=_user_id;
END//

CREATE PROCEDURE PROC_GET_USERINFO_LOGIN (IN _user_login VARCHAR(50), IN _locale VARCHAR(50))
BEGIN
	DECLARE user_id INT;

	SELECT id INTO user_id FROM users WHERE login=_user_login;
	CALL PROC_GET_USERINFO(user_id, _locale);
END//

