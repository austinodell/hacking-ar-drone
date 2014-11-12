<?php 
$CHUNK = 8192; 
$time = time();
$tmpFile = "PUT_FILE_dronepic";
$tmpFileName = "/var/dev/tmp/" . $tmpFile;

        try {
            if (!($putData = fopen("php://input", "r")))
                throw new Exception("Can't get PUT data.");

            $tot_write = 0;

            // Create a temp file
            //if (!is_file($tmpFileName)) {
                fclose(fopen($tmpFileName, "x")); //create the file and close it
                // Open the file for writing
                if (!($fp = fopen($tmpFileName, "w")))
                    throw new Exception("Can't write to tmp file");

                // Read the data a chunk at a time and write to the file
                while ($data = fread($putData, $CHUNK)) {
                    $chunk_read = strlen($data);
                    if (($block_write = fwrite($fp, $data)) != $chunk_read)
                        throw new Exception("Can't write more to tmp file");

                    $tot_write += $block_write;
                } 

	} catch (Exception $e) {
            echo '', $e->getMessage(), "\n";
        }

$newname = "dronepic-" . date(('Y-m-d-H-i'),$time);
if(filesize($tmpFileName > 1800000) {
	exec("UYVYtoRGB 1280 720 1 < " . $tmpFileName . " | RGBtoBMP " . $newname . " .bmp 0 1 1 1280 720");
} else {
	exec("UYVYtoRGB 320 240 1 < " . $tmpFileName . " | RGBtoBMP " . $newname . " .bmp 0 1 1 320 240");
}
exec("rm -f " . $tmpFileName);

if (file_exists($newname . "1.bmp")) {
    header('Content-Description: File Transfer');
    header('Content-Type: application/octet-stream');
    header('Content-Disposition: attachment; filename='.basename($newname . ".bmp"));
    header('Expires: 0');
    header('Cache-Control: must-revalidate');
    header('Pragma: public');
    header('Content-Length: ' . filesize($newname . "1.bmp"));
    readfile($newname . "1.bmp");
    exit;
} else {
	echo 'cannot find file' . "\n";
}
