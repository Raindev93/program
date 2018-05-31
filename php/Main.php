<?php

class Main {
	private $dir;
	private $image;
	
	public function __construct(string $dir) {
		$this->dir = $dir;
	}

	public function init() {
		$image = $this->image($this->filename());
		$result = $image->match();
		return $result;
	}

	private function image(string $fileName) : Image {
		return new Image($fileName);
	}
 
	private function filename() : string {
		$filename = $_FILES['file']['name'];
		return "./$this->dir/" . $filename;
	}
};

?>