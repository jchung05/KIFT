/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 20:27:55 by jchung            #+#    #+#             */
/*   Updated: 2018/04/23 15:26:58 by jchung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <pocketsphinx.h>
#include <sphinxbase/ad.h>
#include <sphinxbase/err.h>
#include <sys/time.h>

const char			*recognize_from_microphone(void);

ps_decoder_t		*ps;
cmd_ln_t			*config;
ad_rec_t			*ad;

int16				adbuf[512];
uint8				utt_started, in_speech;
int32				k;
char const			*hyp;
char const			*decoded_speech;

/**
 ** Remember to use the proper language model and dictionary
 ** when the corpus.txt is trained
 */

int					main(int argc, char **argv)
{
	FILE			*fp;
	time_t			rawtime;
	struct tm		*timeinfo;
	char			buf[80];

	config = cmd_ln_init(NULL, ps_args(), TRUE, 
				"-hmm", MODELDIR "/en-us/en-us",
				"-lm", MODELDIR "/en-us/en-us.lm.bin",
				"-dict", MODELDIR "/en-us/cmudict-en-us.dict",
				"-logfn", "/dev/null",
				NULL);
	if (!config)
	{
		fprintf(stderr, "Failed to create config object, see log for details\n");
		return (-1);
	}

	ps = ps_init(config);
	if (!ps)
	{
		fprintf(stderr, "Failed to create recognizer, see log for details\n");
		return (-1);
	}

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	printf("config done at %s\n", asctime(timeinfo));
	ad = ad_open_dev("sysdefault", (int) cmd_ln_float32_r(config, "-samprate"));

	while(1)
	{
		fp = fopen("history.log", "ab+");
		decoded_speech = recognize_from_microphone();
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buf, 1024, "%D - %T", timeinfo);
		printf("%s: %s\n", buf, decoded_speech);
		fwrite(buf, 1, strlen(buf), fp);
		fwrite(": ", 1, 2, fp);
		fwrite(decoded_speech, 1, strlen(decoded_speech), fp);
		fwrite("\n", 1, 1, fp);
		fclose(fp);
	}
	ad_close(ad);
}

const char			*recognize_from_microphone(void)
{
	ad_start_rec(ad);
	ps_start_utt(ps);
	utt_started = FALSE;
	while(1)
	{
		k = ad_read(ad, adbuf, 512);
		ps_process_raw(ps, adbuf, k, FALSE, FALSE);
		in_speech = ps_get_in_speech(ps);
		if (in_speech && !utt_started)
			utt_started = TRUE;
 		if (!in_speech && utt_started)
		{
			ps_end_utt(ps);
			ad_stop_rec(ad);
			hyp = ps_get_hyp(ps, NULL );
			return (hyp);
		}
	}
}
