package com.example.android.courtcounter;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    final int FREE_THROW = 1;
    final int TWO_POINTS = 2;
    final int THREE_POINTS = 3;
    int scoreA = 0;
    int scoreB = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //displayForTeamA(6);
    }

    public void threePointsA (View view){
        scoreA += THREE_POINTS;
        displayForTeamA(scoreA);
    }

    public void twoPointsA (View view){
        scoreA += TWO_POINTS;
        displayForTeamA(scoreA);
    }

    public void freeThrowA (View view){
        scoreA += FREE_THROW;
        displayForTeamA(scoreA);
    }

    public void threePointsB (View view){
        scoreB += THREE_POINTS;
        displayForTeamB(scoreB);
    }

    public void twoPointsB (View view){
        scoreB += TWO_POINTS;
        displayForTeamB(scoreB);
    }

    public void freeThrowB (View view){
        scoreB += FREE_THROW;
        displayForTeamB(scoreB);
    }

    /**
     * Displays the given score for Team A.
     */
    public void displayForTeamA(int score) {
        TextView scoreView = (TextView) findViewById(R.id.team_a_score);
        scoreView.setText(String.valueOf(score));
    }

    /**
     * Displays the given score for Team A.
     */
    public void displayForTeamB(int score) {
        TextView scoreView = (TextView) findViewById(R.id.team_b_score);
        scoreView.setText(String.valueOf(score));
    }

    public void resetScore (View view) {
        scoreA = 0;
        scoreB = 0;
        displayForTeamA(scoreA);
        displayForTeamB(scoreB);
    }
}
