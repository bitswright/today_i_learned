package main

func main() {
	problem := &TransformToSumTree{}
	execute(problem)
}

func execute(problem Problem) {
	problem.input()
	problem.transformInput()
	problem.solve()
	problem.transformOutput()
	problem.printResult()
}
