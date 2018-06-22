#!/bin/sh

fun_test() {
	echo "fun_test start"
	variable="wuqiang29"
	echo "$variable"
}

fun_test_1() {

	if [ -n "$variable" ]; then
		echo "当前变量variable是$variable"
	fi
}


echo "shanghaixiaoxun"
fun_test
echo "test_var"
fun_test_1
echo "$variable"
