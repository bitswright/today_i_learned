void main() {
    var list1 = [10, 7, 3, 5, 9, 1];

    print(findMax(list1));
}

int findMax(List<int> list) {
    int maxSoFar = -1;
    for(int i = 0; i < list.length; i++) {
        if(list[i] > maxSoFar) {
            maxSoFar = list[i];
        }
    }
    return maxSoFar;
}

