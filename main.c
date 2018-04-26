/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 20:27:55 by jchung            #+#    #+#             */
/*   Updated: 2018/04/25 18:10:21 by jchung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <pocketsphinx.h>
#include <sphinxbase/ad.h>
#include <sphinxbase/err.h>
#include <sys/time.h>

const char			*recognize_from_microphone(void);
void				file_write(const char *);

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

	printf("config done\n");
	ad = ad_open_dev("sysdefault", (int) cmd_ln_float32_r(config, "-samprate"));

	while(1)
	{
		decoded_speech = recognize_from_microphone();
		file_write(decoded_speech);
	}
	ad_close(ad);
}

void				file_write(const char *hyp)
{
	FILE			*fp;
	time_t			rawtime;
	struct tm		*timeinfo;
	char			buf[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buf, 80, "%D - %T", timeinfo);
	fp = fopen("history.log", "ab+");
	printf("%s: %s.\n", buf, hyp);
	fwrite(buf, 1, strlen(buf), fp);
	fwrite(": ", 1, 2, fp);
	fwrite(hyp, 1, strlen(hyp), fp);
	fwrite(".\n", 1, 2, fp);
	fclose(fp);
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
