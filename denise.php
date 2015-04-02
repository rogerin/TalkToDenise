<?php

$msg = $_GET['msg'];

if(empty($msg)) {
	echo "Sem mensagem, nem vamos perder tempo fazendo login na denise.. ela ta descançando..";
} else {

	$ch = curl_init("http://200.217.58.75:8000/Kernel?function=AskAuthKey&Login=welcome&Password=well007");
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
	curl_setopt($ch, CURLOPT_HEADER, 0);
	$token = curl_exec($ch);
	curl_close($ch);

	echo "Esse é o token: " . $token . " <br/>";
	echo "enviando para Denise...";
	flush(); // limpa memoria

	$ch = curl_init("http://200.217.58.75:8000/Agent?function=AgentSpeakInChat&Auth=".$token."&Text=".$msg);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
	curl_setopt($ch, CURLOPT_HEADER, 0);
	$data = curl_exec($ch);
	curl_close($ch);

	echo "Ënviada. <br />";
	echo "Frase enviada: " . $data;

	flush(); // ja disse. 

}

/* agora
	Criar esse servico com PHP, para receber os dados, autentica e enviar.
*/