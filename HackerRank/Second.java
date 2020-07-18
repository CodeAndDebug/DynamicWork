import java.io.BufferedInputStream;
import java.util.Scanner;
import java.util.ArrayList;



public class Second {


  public static boolean EstritamenteCrescente(int[] ar){
    int altera = 0;

    if ((ar[0] > ar[1]){
      altera++;
    }

    for (int i = 1; i < ar.length - 1; i++){
        if ((ar[i-1] < ar[i] && ar[i+1] < ar[i]) || (ar[i-1] > ar[i] && ar[i+1] > ar[i]))
          altera++;
      }
    }

    if (ar[n-1] < ar[n-2]){
      altera++;
    }

      if (altera > 1)
        return false;

        System.out.println("true");
    return true;
  }



  public static void main (String args[]) {
    //Array com a input do utilizador
    int [] ar;
    Scanner stdin;
    int size = 4;

    //Input do utilizador
    stdin = new Scanner(new BufferedInputStream(System.in));
    ar = new int[size];

    for (int i = 0; i < size; i++){
      ar[i] = stdin.nextInt();
    }

    EstritamenteCrescente(ar);


    }
}
