import java.io.BufferedInputStream;
import java.util.Scanner;
import java.util.ArrayList;



public class Try {


  public static int[] rotation(int[] ar, int rot){

    for (int i = 0; i < rot; i++){
      int aux = ar[0];
      for (int j = 0; j < ar.length - 1; j++){
        ar[j] = ar[j+1];
      }
      ar[ar.length - 1] = aux;
    }

    return ar;
  }



  public static void main (String args[]) {
    //Array com a input do utilizador
    int [] ar;
    Scanner stdin;
    int size, rot;

    //Input do utilizador
    stdin = new Scanner(new BufferedInputStream(System.in));
    size = stdin.nextInt(); //Tamanho
    ar = new int[size];
    rot = stdin.nextInt(); //N de rotacoes

    for (int i = 0; i < size; i++){
      ar[i] = stdin.nextInt();
    }

    for(int j = 0; j < size; j++){
      System.out.println(ar[j]);
    }

    int[] new_array = rotation(ar, rot);
    for (int k = 0; k < size; k++){
      System.out.print(new_array[k] + "\t");
    }
    //System.out.println("Resultado " + size);


    }
}
