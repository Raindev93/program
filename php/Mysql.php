<?php
include "php/DBconfig.php";
class Mysql extends DBconfig{
	private $pdo;

	function __construct() {
		parent::__construct();
		$this->pdo = $this->connect();
	}

	public function getImagesList() : array {
		$stmt = $this->pdo->query('SELECT * FROM images');
		$images = [];
		while ($row = $stmt->fetch())
		{
		    $images[] = $row['name'];
		}
		return $images;
	}
}

?>