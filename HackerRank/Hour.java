import java.io.BufferedInputStream;
import java.util.Scanner;
import java.util.ArrayList;



public class Hour {


  public static int hourglass(int[][] ar){

    int max, sum;
    max = sum = 0;

    for (int i = 0; i < (ar.length / 2) + 1; i++){
      for (int j = 0; j < (ar.length / 2) + 1; j++){
        sum = ar[i][j] + ar[i][j+1] + ar[i][j+2] + ar[i+1][j+1] + ar[i+2][j] + ar[i+2][j+1] + ar[i+2][j+2];
        System.out.println("Debug " + ar[i][j] + " " + ar[i][j+1] + " "+ ar[i][j+2] + " "+ ar[i+1][j+1] + " "+ ar[i+2][j] + " "+ ar[i+2][j+1] + " " + ar[i+2][j+2]);

      System.out.println("Soma " + sum + " ");
      if (sum > max)
        max = sum;
      sum = 0;
      }
    }

    return max;
  }



  public static void main (String args[]) {
    //Array com a input do utilizador
    int size = 6;
    int [][] ar = new int[size][size];
    Scanner stdin;

    //Input do utilizador
    stdin = new Scanner(new BufferedInputStream(System.in));

    for (int i = 0; i < size; i++){
      for (int j = 0; j < size; j++){
      ar[i][j] = stdin.nextInt();
    }
  }

  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      System.out.print(ar[i][j] + " ");
    }
    System.out.println();
  }

  System.out.println("Max sum: " + hourglass(ar));

    }
}
