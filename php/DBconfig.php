<?php
class DBconfig {
    protected $host;
    protected $userName;
    protected $dbName;
    protected $charset;
    protected $pass;

    function __construct() {
        $this->hostName = '';
        $this->userName = '';
        $this->dbName = '';
        $this->charset = '';
        $this->pass = '';
    }	
    protected function connect() : PDO {

    	$dsn = "mysql:host=$this->hostName;dbname=$this->dbName;charset=$this->charset";
		$opt = [
		    PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,
		    PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
		    PDO::ATTR_EMULATE_PREPARES   => false,
		];
		return new PDO($dsn, $this->userName, $this->pass, $opt);
    }
}
?>