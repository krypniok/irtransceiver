<?php
// Aktuelles Datum im YYYY-MM-DD Format
$currentDate = date('Y-m-d');

// URL für das aktuelle Datum
//$url = "https://www.tvmovie.de/tv/fernsehprogramm-heute-abend?date=$currentDate&group=6#group5";
$url = "https://www.tvmovie.de/tv/programm-jetzt?date=$currentDate&group=6#group6";

// HTML-Inhalt von der URL abrufen
$html = file_get_contents($url);

// Sendungsdaten extrahieren
preg_match_all('/<section class="item">.*?<span class="h2">(.*?)<\/span>.*?<time itemprop="startDate">(.*?)<\/time>.*?<span itemprop="name"[^>]*>(.*?)<\/span>.*?<span itemprop="genre">(.*?)<\/span>/s', $html, $shows, PREG_SET_ORDER);

// Ausgabe
foreach ($shows as $show) {
    // Sendername ist hier Teil des Match
    $channelName = trim($show[1]); // Sendername
    $time = $show[2];               // Zeit
    $name = trim(strip_tags($show[3])); // <span> Tags entfernen
    $genre = trim($show[4]);        // Genre
    
    echo "Channel: $channelName, Time: $time, Show: $name, Genre: $genre\n";
}

?>

