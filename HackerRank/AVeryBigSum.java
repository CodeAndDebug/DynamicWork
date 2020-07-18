import java.io.BufferedInputStream;
import java.util.Scanner;
import java.util.ArrayList;



public class AVeryBigSum {


  public static long sum(int[] ar){
    long soma = 0;

    for (int i = 0; i < ar.length; i++){
      soma += ar[i];
    }

    return soma;
  }



  public static void main (String args[]) {
    //Array com a input do utilizador
    int [] ar;
    Scanner stdin;
    int size;

    //Input do utilizador
    stdin = new Scanner(new BufferedInputStream(System.in));
    size = stdin.nextInt(); //Tamanho
    ar = new int[size];

    for (int i = 0; i < size; i++){
      ar[i] = stdin.nextInt();
    }

    System.out.println("Resultado: " + sum(ar));
    }
}
