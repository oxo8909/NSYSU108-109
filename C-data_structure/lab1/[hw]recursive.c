#include <stdio.h>

int main(void){
	printf("binominal(6, 4) = %d", binominal(6, 4));
	printf("\nAckerman(3, 2) = %d", ackerman(3, 2));
	return 0;
}

//please implement binominal recursive function here
int binominal(int n, int m){
	if(n > m && m > 0){
		return binominal(n - 1, m) + binominal(n - 1, m - 1);
	}else{
		return 1;
	}
	return 0;
}


//please implement ackerman recursive function here
int ackerman(int m, int n){
	if(m == 0){
		return (n + 1);
	}else if(n == 0){
		return ackerman(m - 1, 1);
	}else{
		return ackerman(m - 1, ackerman(m, n - 1));
	}
	return 0;
}

