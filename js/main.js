$(document).ready(function(){
	var uploadForm = $('#upload-form');

	uploadForm.submit(function(e) {
		e.preventDefault();

		var fd = new FormData();
        var files = $('#file')[0].files[0];
        fd.append('file',files);

        $.ajax({
			xhr: function() {
				$('.progress').show();
			    var xhr = new window.XMLHttpRequest();

			    xhr.upload.addEventListener("progress", function(e) {
			      if (e.lengthComputable) {
			        var percent = e.loaded / e.total;
			        percent = parseInt(percent * 100);
			        $('.progress-bar').css('width',percentComplete+'%')
			        if (percent === 100) {
			        	$('.progress-bar').css('width','0%')
			        	$('.progress').hide();
			        }

			      }
			    }, false);

			    return xhr;
			},
            url: 'upload.php',
            type: 'post',
            data: fd,
            dataType: 'json',
            contentType: false,
            processData: false,
            success: function(response){
            	if (response.status) {
            		$('.status > h4').html('template found');
            		$('.status').prepend('<img src="' + response.name + '" />')
            	} else {
            		$('.status > h4').html('template not found');
            	}
            },
        });
		return;
	})
});