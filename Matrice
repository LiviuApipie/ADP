package matrix_Add_with_Thread;

import java.util.Random;

public class matrix {

	static int n=10;
	static int[][] matrice1 = new int[n][n];
	static int[][] matrice2 = new int[n][n];
	static int[][] inmultire = new int[n][n];
	
	public static void main(String [] args){

 		Random rand = new Random();

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				matrice1[i][j]=rand.nextInt(10)+1;
			}
		}
    
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				matrice2[i][j]=rand.nextInt(10);
			}
		}

		try{        
			Multiply multiply = new Multiply(n,n);
        
			for(int nr = 0; nr<n; nr++){
				MatrixMultiplier thread = new MatrixMultiplier(multiply);
				Thread th = new Thread(thread);
				th.start();
				th.join();
			}
			
			
		}catch (Exception e) {
			e.printStackTrace();
		}

    
		System.out.println("\n\nResult:");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				System.out.print(inmultire[i][j]+" ");
			}
			System.out.println();
		}
		
	}

}

   
   class Multiply extends matrix {

	   private int i;
	   private int j;
	   private int chance;

	   		public Multiply(int i, int j){
	   			this.i=i;
	   			this.j=j;
	   			chance=0;
	   		}

	   		public synchronized void multiplyMatrix(){

	   			int sum=0;
	   			int a=0;
	   			
	   			for(a=0;a<i;a++){
	   				sum=0;
	   				for(int b=0;b<j;b++){
	   					sum=sum+matrice1[chance][b]*matrice2[b][a];
	   				}
	   				inmultire[chance][a]=sum;
	   			}
	   			
	   			if(chance>=i)
	   				return;
	   			chance++;  			
	   			
	   		}
   }
   class MatrixMultiplier implements Runnable {

    	 private final Multiply mul;

    	 public MatrixMultiplier(Multiply mul){
    		 this.mul=mul;
    	 }

	public void run() {
    	mul.multiplyMatrix();
	}
}
