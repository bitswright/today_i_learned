package main

import "fmt"

type TreeNode struct {
	val   int
	left  *TreeNode
	right *TreeNode
}

type TransformToSumTree struct {
	n         int
	treeArray []int
	root      *TreeNode
	res       []int
}

func (problem *TransformToSumTree) input() {
	fmt.Print("Enter number of nodes (n) : ")
	fmt.Scan(&problem.n)

	problem.treeArray = make([]int, problem.n)
	fmt.Print("Enter the tree nodes : ")
	for i := range problem.n {
		fmt.Scan(&problem.treeArray[i])
	}
}

func (problem *TransformToSumTree) transformInput() {
	problem.root = generateTreeFromArray(0, problem.n, &problem.treeArray)
}

func generateTreeFromArray(i int, n int, arr *[]int) *TreeNode {
	if i >= n {
		return nil
	}
	left := generateTreeFromArray(2*i+1, n, arr)
	right := generateTreeFromArray(2*i+2, n, arr)
	root := &TreeNode{val: (*arr)[i], left: left, right: right}
	return root
}

func (problem *TransformToSumTree) solve() {
	transformToSumTree(problem.root)
}

func (problem *TransformToSumTree) transformOutput() {
	problem.res = make([]int, problem.n)
	generateArrayFromTree(0, problem.root, &problem.res)
}

func generateArrayFromTree(i int, root *TreeNode, arr *[]int) {
	if root == nil {
		return
	}
	(*arr)[i] = root.val
	generateArrayFromTree(2*i+1, root.left, arr)
	generateArrayFromTree(2*i+2, root.right, arr)
}

func (problem *TransformToSumTree) printResult() {
	fmt.Printf("Result: %v\n", problem.res)
}

func transformToSumTree(root *TreeNode) {
	transformToSumTreeInternal(root)
}

func transformToSumTreeInternal(root *TreeNode) int {
	if root == nil {
		return 0
	}
	leftSum := transformToSumTreeInternal(root.left)
	rightSum := transformToSumTreeInternal(root.right)
	rootValue := root.val
	root.val = leftSum + rightSum
	return leftSum + rootValue + rightSum
}
