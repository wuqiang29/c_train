-- Delete three tables;
#Dele the tables
/*add artist table*/

/*上面是sql文件的三种注释方便，注意第一种注释方法双长线(--)后必须要跟一个空格*/

/*如下delete from 清空三个列表中的数据*/
delete from track;
delete from cd;
delete from artist;

/*如下删除三个列表*/
DROP table track;
DROP table cd;
DROP table artist;



/*创建表*/
CREATE TABLE cd(id INTEGER AUTO_INCREMENT NOT NULL PRIMARY KEY,title VARCHAR(70) NOT NULL,artist_id INTEGER NOT NULL,catalogue VARCHAR(30) NOT NULL,notes VARCHAR(100));

CREATE TABLE track(cd_id INTEGER NOT NULL,track_id INTEGER NOT NULL,title VARCHAR(70),PRIMARY KEY(cd_id,track_id));

CREATE TABLE artist(id INTEGER AUTO_INCREMENT  NOT NULL PRIMARY KEY,name VARCHAR(100) NOT NULL);



insert into artist(id,name) values(1,'Pink Floyd');
insert into artist(id,name) values(2,'Genesis');
insert into artist(id,name) values(3,'Einaudi');
insert into artist(id,name) values(4,'Melanie C');
insert into artist(id,name) values(5,'Esen Cheng');


insert into cd(id,title,artist_id,catalogue) values(1,'Dark Side of the Moon',1,'B000024D4P');
insert into cd(id,title,artist_id,catalogue) values(2,'Wish You Were Here',1,'B000024D4S');
insert into cd(id,title,artist_id,catalogue) values(3,'A Trick of the Tail',2,'B000024EXM');
insert into cd(id,title,artist_id,catalogue) values(4,'Selling England By the Pound',2,'B000024E9M');
insert into cd(id,title,artist_id,catalogue) values(5,'I Giorni',3,'B000071WEV');
insert into cd(id,title,artist_id,catalogue) values(6,'Northern Star',4,'B00004YMST');
insert into cd(id,title,artist_id,catalogue) values(7,'Black White Gray',5,'B000024D4D');

insert into track(cd_id,track_id,title) values(1,1,'Speak to me');
insert into track(cd_id,track_id,title) values(1,2,'Breathe');

insert into track(cd_id,track_id,title) values(2,1,'Shine on you crazy diamond');
insert into track(cd_id,track_id,title) values(2,2,'Welcome to the machine');
insert into track(cd_id,track_id,title) values(2,3,'Have a cigar');
insert into track(cd_id,track_id,title) values(2,4,'Wish you were here');
insert into track(cd_id,track_id,title) values(2,5,'shine on you crazy diamond pt.2');

insert into track(cd_id,track_id,title) values(5,1,'Melodia Aficana (part 1)');
insert into track(cd_id,track_id,title) values(5,2,'I due fiumi');
insert into track(cd_id,track_id,title) values(5,3,'In un\'altra vita');

insert into track(cd_id,track_id,title) values(6,1,'Closer');
insert into track(cd_id,track_id,title) values(6,2,'Feel The Sun');
insert into track(cd_id,track_id,title) values(7,1,'Ten years');


 
/* 
SELECT artist.name, cd.title AS "CD Title", track.track_id, track.title AS "Track" FROM artist, cd, track WHERE artist.id = cd.artist_id AND track.cd_id = cd.id AND track.track_id < 3

insert into t_visual_user_domain(`user_id`,`domain`,`group`) select id,'www.baidu.com' as domain,`group` from t_visual_user;


SELECT DISTINCT artist.id, cd.id FROM artist, cd WHERE artist.id = cd.artist_id AND (artist.name LIKE '%%Symphony%%' OR cd.title LIKE '%%Symphony%%' OR cd.catalogue LIKE '%%Symphony%%')

执行如下命令自动导入数据
\. insert_data.sql
*/
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 