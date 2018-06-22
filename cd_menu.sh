#!/bin/sh


#global variable
menu_choice=""
current_cd=""
title_file="title.cdb"
tracks_file="tracks.cdb"
temp_file=/home/wuqiang/share/test_we/c_train/cdb.$$
trap 'rm -f $temp_file' EXIT

get_return() {
	echo -e "Press return \c"
	read x
	return 0
}

get_confirm() {
	echo -e "Are you sure? \c"
	while true
	do
		read x
		case "$x" in
			y | yes | Y | YES |Yes )
			return 0;;
			n | no | NO  | No )
			echo
			echo "Cancelled"
			return 1;;
			* )
			echo "Please enter yes or no";;
		esac	
	done	
}

set_menu_choice() {
	clear
	echo "Options :-"
	echo
	echo " a) Add new CD"
	echo " f) Find CD"
	echo " c) Count the CDs and tracks in the catalog"
	echo " b) More titles information"
	
	if [ "$cdcatnum" != "" ]; then
		echo " l) List tracks on $cdtitle"
		echo " r) Remove $cdtitle"
		echo " u) Update tracks information for $cdtitle"
	fi
	echo " q) Quit"
	echo
	echo -e "Please enter choice then press return \c"
	read menu_choice
	return
}

insert_title() {
	echo $* >> $title_file
	return
}

insert_track() {
	echo $* >> $tracks_file
	return
}

#输入曲目信息
add_record_tracks() {
	echo "Enter track information for this CD"
	echo "When no more tracks enter q"
	cdtrack=1
	cdttitle=""
	while [ "$cdttitle" != "q" ]
	do
		echo -e "Track $cdtrack, track title? \c"
		read tmp
		#删掉第一个逗号及其右边的字符串
		cdttitle=${tmp%%,*}
		if [ "$tmp" != "$cdttitle" ]; then
			echo "Sorry, no commas allowed"
			continue
		fi
		if [ -n "$cdttitle" ]; then
			if [ "$cdttitle" != "q" ]; then
				insert_track $cdcatnum,$cdtrack,$cdttitle
			fi
		else
			cdtrack=$((cdtrack-1))
		fi
		cdtrack=$((cdtrack+1))
	done
}

#输入标题信息
add_records() {
	#Prompt for the initial information
	
	echo -e "Enter catalog name \c"
	read tmp
	cdcatnum=${tmp%%,*}
	
	echo -e "Enter title \c"
	read tmp
	cdtitle=${tmp%%,*}
	
	echo -e "Enter type \c"
	read tmp
	cdtype=${tmp%%,*}
	
	echo -e "Enter artist/composer \c"
	read tmp
	cdac=${tmp%%,*}
	
	#check get_confirm for new tracks
		
	echo "About to add entry"
	echo "$cdcatnum $cdtitle $cdtype $cdac"
	
	#if confirmed the append it to the title file
	
	if get_confirm ; then
		insert_title $cdcatnum,$cdtitle,$cdtype,$cdac
		add_record_tracks
	else
		remove_records
	fi
	return		
}

#在唱片标题文件中查找唱片有关资料
find_cd() {
	if [ "$1" = "n" ]; then
		asklist=n
	else
		asklist=y
	fi
	
	cdcatnum=""
	
	echo -e "Enter a string to searchstr for in tht CD title \c"
	read searchstr
	if [ "$searchstr" = "" ]; then
		return 0;
	fi
	
	grep "$searchstr" $title_file > $temp_file
	
	set $(wc -l $temp_file)
	linesfound=$1
	case "$linesfound" in
		0)	echo "sorry nothing found"
				get_return
				return 0
				;;
		1)	;;
		2)	echo "Sorry, not unique."
			echo "Found the following"
			cat $temp_file
			get_return
			return 0
			;;
	esac
	
	IFS=","	
	read cdcatnum cdtitle cdtype cdac < $temp_file	
	IFS=" "
	
	if [ -z "$cdcatnum" ]; then
		echo "Sorry, could not exact catalog field form $temp_file"
		get_return
		return 0
	fi
	
	echo 
	echo Catalog number: $cdcatnum
	echo Title: $cdtitle
	echo Type: $cdtype
	echo Artist/Composer: $cdac
	echo
	get_return
	
	if [ "$asklist" = "y" ]; then
		echo -e "View tracks for this CD? \c"
			read x
		if [ "$x" = "y" ]; then
			echo
			list_tracks
			echo
		fi
	fi
	return 1	
}

#重新输入唱片标题信息
update_cd() {
	if [ -z "$cdcatnum" ]; then
		echo "You must select a CD first"
		find_cd n
	fi
	
	if [ -n "$cdcatnum" ]; then
		echo "Current tracks are:-"
		list_tracks
		echo
		
		echo "This will re-enter the tracks for $cdtitle"
		get_confirm && {
			grep -v "^${cdcatnum}," $tracks_file > $temp_file
			mv $temp_file $tracks_file
			echo
			add_record_tracks	
		}
	fi
	return
}

#统计唱片个数和曲目个数
count_cds() {
	set $(wc -l $title_file)
	num_titles=$1
	echo "CD title-"
	cat $2
	set $(wc -l $tracks_file)
	num_tracks=$1
	
	echo
	echo 
	
	echo "CD tracks-"
	cat $2
	echo  found $num_titles CDs, with a total of $num_tracks tracks
	get_return
	return
}

#从数据库中删除数据项
remove_records() {
	if  [ -z "$cdcatnum" ]; then
		echo You must select a CD first
		find_cd n
	fi
	
	if [ -n "$cdcatnum" ]; then
		echo "You are about to delete $cdtitle"
		get_confirm && {
			grep -v "^${cdcatnum}," $title_file > $temp_file
			mv $temp_file $title_file
			cdcatnum=""
			echo Entry removed
		}
	get_return
	fi
	return
}

list_tracks() {
	if [ "cdcatnum" = "" ]; then
		echo no CD selected yet
		return
	else
		#在文件$tracks_file中搜索以$cdcatnum开始(通过^实现)，其后紧跟一个逗号，注意{}花括号是为了实现逗号紧跟
		grep "^${cdcatnum}," $tracks_file > $temp_file
		num_tracks=$(wc -l $temp_file)
		
#		echo "测试 查看 $num_tracks"
		
		if [ "$num_tracks" = "0" ]; then
			echo no tracks found for $cdtitle
		else {
			echo
			echo "$cdtitle :-"
			echo
			#cut $temp_file文件，以逗号为分隔符，打印出第二块及其以后的内容
			cut -f 2- -d , $temp_file
			echo		
		} | ${PAGER:-more}
		fi
	fi
	get_return
	return
 }

#主程序
rm -f $temp_file
if [ ! -f $title_file ]; then
	touch $title_file
fi

if [ ! -f $tracks_file ]; then
	touch $tracks_file
fi
	
clear
echo 
echo
echo "Mini CD Manage"
sleep 1

quit=n

while [ "$quit" != "y" ]
do
	set_menu_choice
	case "$menu_choice" in
	a) add_records;;
	r) remove_records;;
	f) find_cd y;;
	u) update_cd;;
	c) count_cds;;
	l) list_tracks;;	
	b)
		echo 
		more $title_file
		echo
		get_return;;
	q | Q) quit=y;;
	*) echo "Sorry, Choice not recognized";;
	esac
done

#Tidy up and leave

rm -f $temp_file
echo "Finished"
exit 0
