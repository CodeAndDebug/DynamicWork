import java.io.BufferedInputStream;
import java.util.Scanner;
import java.util.ArrayList;



public class First {


  public static int MaiorProduto(int[] ar){
    int prod, maior;
    prod = maior = 0;

    for (int i = 0; i < ar.length - 1; i++){
      prod = ar[i] * ar[i + 1];
      if (prod > maior)
        maior = prod;
    }
    return maior;
  }



  public static void main (String args[]) {
    //Array com a input do utilizador
    int [] ar;
    Scanner stdin;
    int size = 6;
    ar = new int [size];
    
    //Input do utilizador
    stdin = new Scanner(new BufferedInputStream(System.in));

    for (int i = 0; i < size; i++){
      ar[i] = stdin.nextInt();
    }


    MaiorProduto(ar);

    }
}
