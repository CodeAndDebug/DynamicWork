import java.io.BufferedInputStream;
import java.util.Scanner;
import java.util.ArrayList;



public class Triplets {

  public static void verifica(int[] ar1, int[] ar2){
    int acum1, acum2;
    acum1 = acum2 = 0;

    for (int i=0; i < 3; i++){
      if (ar1[i] > ar2[i]){
          acum1++;
      } else if (ar2[i] > ar1[i]){
        acum2 += 1;
      }
    }

    System.out.println(acum1 + " " + acum2);

  }



  public static void main (String args[]) {
    //Array com a input do utilizador
    int [] ar1,ar2;
    ar1 = new int [3];
    ar2 = new int [3];
    Scanner stdin;

    //Input do utilizador
    stdin = new Scanner(new BufferedInputStream(System.in));

    for (int i = 0; i < ar1.length; i++){
      ar1[i] = stdin.nextInt();
    }

    for (int j = 0; j < ar2.length; j++){
      ar2[j] = stdin.nextInt();
    }


    verifica(ar1, ar2);

    }
}
