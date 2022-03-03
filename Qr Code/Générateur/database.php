<?php

    define('HOST' , 'localhost');
    define('DB_NAME' , 'personnel'); // nom de la base de donné 
    define('USER' , 'portail'); // utilisatuer consierge
    define('PASS', 'portail'); // mdp

    /* Connection à la base de donnée */ 
    try 
    {
        $db = new PDO("mysql:host=". HOST . ";dbname". DB_NAME , USER , PASS); /* connection au compte admin */
        $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION); /* teste de connection a la base de donner */
        echo "connection correct";
    }

    /* Traitement de l'exception */ 
     catch(PDOException $e)
        {
            echo $e; // affiche l'erreur
        }
    
        

