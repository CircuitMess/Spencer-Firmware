$(document).ready(function(){
	const $select = $("#ssid");
	const $dropdown = $(".dropdown");
	var settings = [ "", "", "", "" ];

	const Success = "Settings saved.";
	const NetworkError = "Error. Please make sure you are connected to Spencer."
	const SpencerError = "Error. Please try restarting Spencer."

	function fillSelect(networks){
		$select.empty();

		function addItem(item, prepend){
			const el = $("<option />");
			el.attr("value", item);
			el.html(item);

			prepend && $select.prepend(el) || $select.append(el);
		}

		for(var i = 0; i < networks.length; i++){
			addItem(networks[i], false);
		}

		i = networks.indexOf(settings[0]);
		if(i === -1){
			i = 0;
			if(settings[0] !== ""){
				addItem(settings[0], true);
			}
		}

		if($select.children().length === 0){
			addItem("", false);
		}

		$select.children().eq(i).attr("selected", "");
		$select.val($select.children().eq(i).attr("value"));
	}

	function fillDropdown(){
		const modal = $dropdown.children(".modal");

		modal.empty();

		$select.children().each(function(j){
			const option = $(this);

			const item = $("<a />");
			item.addClass("item");
			item.data("value", option.attr("value"));
			item.html(option[0].innerHTML);
			modal.append(item);
		});

		if(modal.children().length === 1 && modal.children()[0].innerHTML === ""){
			$dropdown.children(".selected").html("No networks found");
			modal.empty();
			return;
		}

		const selected = $select.children("[selected]")[0];
		$dropdown.children(".selected").html(selected && selected.innerHTML || "&nbsp;");

		applyEvents();
	}

	function fillSettings(){
		$("#pass").val(settings[1]);
		$("#tts").val(settings[2]);
		$("#stt").val(settings[3]);
	}

	function collectSettings(){
		const selected = $select.children("[selected]")[0];
		settings = [
			selected && selected.value || "",
			$("#pass").val(),
			$("#tts").val(),
			$("#stt").val()
		];
	}

	function applyEvents(){
		$(".dropdown .modal .item").click(function(e){
			e.preventDefault();

			const el = $(this);
			const modal = el.parent();

			const val = el.data("value");
			$select.children().removeAttr("selected");
			$select.children("[value='" + val + "']").attr("selected", "");
			$select.val(val);

			$dropdown.children(".selected").html(el.html());

			modal.removeClass("shown");
			modal.slideUp();

			return false;
		});
	}

	$(".toggleable .btn").click(function(e){
		e.preventDefault();

		const el = $(this);
		const input = el.siblings("input");

		if(input.attr("type") === "password"){
			input.attr("type", "text");
		}else{
			input.attr("type", "password");
		}

		return false;
	});

	$(".dropdown .selected").click(function(e){
		e.preventDefault();
		const modal = $(this).siblings(".modal");

		if(modal.children().length === 0){
			modal.removeClass("shown");
			modal.slideUp();
			return false;
		}

		if(modal.hasClass("shown")){
			modal.removeClass("shown");
			modal.slideUp();
		}else{
			modal.addClass("shown");
			modal.slideDown();
		}

		return false;
	});

	$(".field .button").click(function(e){
		e.preventDefault();

		if($(".field .button").hasClass("active")) return;
		scanNetworks();

		return false;
	});

	$("form").submit(function(e){
		e.preventDefault();

		const button = $("#submit");
		if(button.hasClass("disabled")) return;
		button.addClass("disabled");

		$("#status").slideUp();

		collectSettings();

		const data = {
			"ssid": settings[0],
			"pass": settings[1],
			"tts": settings[2],
			"stt": settings[3],
		};

		$.ajax({
			type: "POST",
			url: "/save",
			data: data,
			success: function(data, status, xhr){
				button.removeClass("disabled");

				if(data === "err"){
					$("#status p").html(SpencerError);
					$("#status").slideDown();
					return;
				}

				settings = data.split("\n");

				$("#status p").html(Success);
				$("#status").slideDown();
			},
			error: function(xhr, status, error){
				button.removeClass("disabled");
				$("#status p").html(NetworkError);
				$("#status").slideDown();
			}
		});

		return false;
	});

	function scanNetworks(){
		const button = $(".field .button");
		button.addClass("active");

		const modal = $dropdown.children("modal");
		modal.removeClass("shown");
		modal.slideUp();

		$("#status").slideUp();

		$.ajax({
			type: "POST",
			url: "/scan",
			success: function(data, status, xhr){
				const networks = data.split("\n");
				fillSelect(networks);
				fillDropdown();
				button.removeClass("active");
			},
			error: function(xhr, status, error){
				$("#status p").html(NetworkError);
				$("#status").slideDown();
				button.removeClass("active");
			}
		});
	}

	$("#button").addClass("disabled");
	$.ajax({
		type: "POST",
		url: "/get",
		success: function(data, status, xhr){
			$("#button").removeClass("disabled");
			settings = data.split("\n");

			fillSettings();
			fillSelect([ settings[0] ]);
			fillDropdown();

			scanNetworks();
		},
		error: function(xhr, status, error){
			$("#button").removeClass("disabled");
			$("#status p").html(NetworkError);
			$("#status").slideDown();
		}
	});
});