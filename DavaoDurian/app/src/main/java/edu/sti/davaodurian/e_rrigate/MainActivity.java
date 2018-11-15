package edu.sti.davaodurian.e_rrigate;

import android.content.Intent;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;

public class MainActivity extends AppCompatActivity {

    RelativeLayout relative1, relative2;
    Button btnLogin;

    Handler h = new Handler();
    Runnable run = new Runnable() {
        @Override
        public void run() {
            relative1.setVisibility(View.VISIBLE);
            relative2.setVisibility(View.VISIBLE);
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        relative1 = (RelativeLayout) findViewById(R.id.relative1);
        relative2 = (RelativeLayout) findViewById(R.id.relative2);

        h.postDelayed(run, 3000);

        btnLogin = (Button) findViewById(R.id.btnLogin);
        btnLogin.setOnClickListener((View.OnClickListener) this);
    }

    public void onClick(View view) {

        Intent in = new Intent(this, Dashboard.class);
        startActivity(in);
    }
}
