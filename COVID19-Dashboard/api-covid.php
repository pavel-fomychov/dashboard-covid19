<?php
header('Content-Type: application/json;charset=utf-8');

$auth_key = '<YOUR_AUTH_KEY>';  // Заменить на сгенерировать API ключ

if ($_GET['auth-key'] == $auth_key){
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, 'http://covid.vinteq.in/api/get_data/?country='.$_GET['country']);
    curl_setopt($ch, CURLOPT_HTTPHEADER, ['auth-key: '.$_GET['auth-key']]);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "GET");
    curl_setopt($ch, CURLOPT_HEADER, 0);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
    $result = json_decode(curl_exec($ch));
    curl_close($ch);

	$output = [
		'day' => $result->live_data->day,
        'population' => round((intval($result->live_data->cases->total) / intval($result->live_data->population)) * 100, 2),
        'cases_new' => $result->live_data->cases->new,
        'cases_active' => $result->live_data->cases->active,
        'cases_recovered' => $result->live_data->cases->recovered,
		'cases_precent' => round((intval($result->live_data->cases->recovered) / intval($result->live_data->cases->total)) * 100, 2),
        'cases_total' => $result->live_data->cases->total,
        'deaths_new' => $result->live_data->deaths->new,
        'deaths_total' => $result->live_data->deaths->total,
    ];

    echo json_encode($output);
} else {
    echo 'Good bay!';
}
?>