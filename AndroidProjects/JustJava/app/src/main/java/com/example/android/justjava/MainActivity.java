/**
 * IMPORTANT: Make sure you are using the correct package name. 
 * This example uses the package name:
 * package com.example.android.justjava
 * If you get an error when copying this code into Android studio, update it to match teh package name found
 * in the project's AndroidManifest.xml file.
 **/

package com.example.android.justjava;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.text.NumberFormat;

/**
 * This app displays an order form to order coffee.
 */
public class MainActivity extends AppCompatActivity {

    int quantity = 2; //Tem que começar com 2

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    /**
     * This method is called when the order button is clicked.
     */

    public void submitOrder(View view) {
        //displayPrice(quantity * price);
        //String message = "Total: " + totalPrice + "€\n";
        //message = message + "Thank you!";
        //displayMessage(message);

        EditText nameInput = (EditText) findViewById(R.id.name_field);
        String name = nameInput.getText().toString();

        CheckBox checkView = (CheckBox) findViewById(R.id.checkbox_id);
        boolean hasWhippedCream = checkView.isChecked();

        CheckBox chocolateView = (CheckBox) findViewById(R.id.chocolate_checkbox);
        boolean hasChocolate = chocolateView.isChecked();

        int totalPrice = calculatePrice(hasWhippedCream, hasChocolate);
        String summary = createOrderSummary(totalPrice, hasWhippedCream, hasChocolate, name);
        /*displayMessage(summary);*/

        //String subject = "JustJava order for " + name;

        String subject = getString(R.string.order_summary_email_subject, name);

        Intent intent = new Intent(Intent.ACTION_SENDTO);
        intent.setData(Uri.parse("mailto:"));
        intent.putExtra(Intent.EXTRA_SUBJECT, subject);
        intent.putExtra(Intent.EXTRA_TEXT, summary);

        if (intent.resolveActivity(getPackageManager()) != null){
            startActivity(intent);
        }
    }

    /**
     * This method displays the given quantity value on the screen.
     */
    private void display(int number) {
        TextView quantityTextView = (TextView) findViewById(R.id.quantity_text_view);
        quantityTextView.setText("" + number);
    }

    /**
     * This method displays the given price on the screen.

    private void displayPrice(int number) {
        TextView priceTextView = (TextView) findViewById(R.id.order_summary_text_view);
        priceTextView.setText(NumberFormat.getCurrencyInstance().format(number));
    }*/

    /*This method increases the quantity of the coffees ordered*/
    public void increment(View view){
        if (quantity == 100){
            Toast.makeText(this, "You cannot have more than 100 coffees", Toast.LENGTH_SHORT).show();
            return;
        }

        quantity = quantity + 1;
        display(quantity);
    }

    /*This method decreases the quantity of the coffees ordered*/
    public void decrement(View view){
        if (quantity == 1){
            Toast.makeText(this, "You cannot have less than 1 coffee", Toast.LENGTH_SHORT).show();
            return;
        }

        quantity = quantity - 1;
        display(quantity);
    }

    /**
     * This method displays the given text on the screen.
     */
    /*private void displayMessage(String message) {
        TextView orderSummaryTextView = (TextView) findViewById(R.id.order_summary_text_view);
        orderSummaryTextView.setText(message);
    }*/

    private int calculatePrice (boolean hasWhippedCream, boolean hasChocolate){
        int basePrice = 5;

        if (hasWhippedCream){
            basePrice += 1;
        }

        if (hasChocolate){
            basePrice += 2;
        }

        return quantity * basePrice;
    }


    /*private void checkWhippedCream (){
        CheckBox checkView = (CheckBox) findViewById(R.id.checkbox_id);
        boolean hasWhippedCream = checkView.isChecked();
    }*/

    private String createOrderSummary (int orderPrice, boolean hasWhippedCream, boolean hasChocolate, String name){
        return getString(R.string.order_summary_name, name) +
                "\n" + getString(R.string.order_summary_whipped_cream, hasWhippedCream) +
                "\n" + getString(R.string.order_summary_chocolate, hasChocolate) +
                "\n" + getString(R.string.order_summary_quantity, quantity) + "\n" + getString(R.string.order_summary_price, orderPrice + " €"/*NumberFormat.getCurrencyInstance().format(orderPrice)*/) + "\n" + getString(R.string.thank_you);

        /*return getString(R.string.order_summary_name, name) +
                "\nAdd whipped cream? " + hasWhippedCream +
                "\nAdd chocolate? " + hasChocolate +
                "\nQuantity: " + quantity + "\nTotal: " + orderPrice + "€\n" + getString(R.string.thank_you);*/
    }

}