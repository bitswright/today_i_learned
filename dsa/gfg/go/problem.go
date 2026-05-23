package main

type Problem interface {
	input()
	transformInput()
	solve()
	transformOutput()
	printResult()
}
