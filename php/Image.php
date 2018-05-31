<?php
class Image {
	private $filename;
	private $templateDir;

	public function __construct(string $filename) {
		$this->filname = $filename;
		$this->templateDir = 'templates';
	}

	public function match() : array{
		$mysql = new Mysql();
		$images = $this->parse($mysql->getImagesList());
		$result = $this->find($images, 20);

		if ($result > 0) {
			return json_encode([
				'status' => 1,
				'name' => $result
			]);
		}
		return json_encode([
			'status' => 0
		]);
	}

	private function find(array $images, int $threshold) : int {
		$path_to_library_dir="/opencv2";
		$path_to_binary="/binary";
		foreach($images as $image){
			$command = 'export LD_LIBRARY_PATH="' . $path_to_library_dir .'"; ' . $path_to_binary." $this->filename $image";
			exec($command,$out);
		}

		$max = array_keys($out, max($out));
		if ($out[$max[0]] > $threshold)
			return $max[0];
		return -1;
	}

	private function parse(array $images) : array {
		$result = [];
		foreach($images as $image) {
			$result[] = "$this->templateDir/".$image;
		}
		return $result;
	}

}
?>