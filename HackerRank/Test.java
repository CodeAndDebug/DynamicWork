import java.io.BufferedInputStream;
import java.util.Scanner;
import java.util.ArrayList;



public class Test {


  public static int alg(int[] array){
    int sum = 0;

    for (int i = 0; i < array.length; i++)
      //System.out.println(args[i]);
      sum += array[i];

    return sum;
  }



  public static void main (String args[]) {
    //Array com a input do utilizador
    int [] array;
    //ArrayList<Integer> values = new ArrayList<>();

    //Input do utilizador
    Scanner stdin = new Scanner(new BufferedInputStream(System.in));
    int linhas = stdin.nextInt();
    array = new int[linhas];

    for (int i = 0; i < linhas; i++){
      //values.add(stdin.nextInt());
      array[i] = stdin.nextInt();
    }

    for(int x = 0; x < linhas; x++){
      System.out.println(array[x]);
    }


    System.out.println("Resultado " + alg(array));

    }
}
