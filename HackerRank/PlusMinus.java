import java.io.BufferedInputStream;
import java.util.Scanner;
import java.util.ArrayList;



public class PlusMinus {


  public static String check(int[] ar){
    int pos, neg, zero;
    float size;

    pos = neg = zero = 0;

      for (int i=0; i < ar.length; i++){
        if (ar[i] == 0){
          zero += 1;
        } else if (ar[i] > 0){
          pos += 1;
        }
        else {
          neg += 1;
        }
      }

      size = ar.length;

      System.out.printf("%.6f\n%.6f\n%.6f\n",pos/size, neg/size, zero/size);
      return pos/size + "\n" + neg/size + "\n" + zero/size;

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


    check(ar);

    }
}
