/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pendejada.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalpart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 04:43:48 by gmalpart          #+#    #+#             */
/*   Updated: 2018/05/12 07:05:45 by gmalpart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

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

t_kift				*handler;




/**
** Remember to use the proper language model and dictionary
** when the corpus.txt is trained
**
** ps_args when no argument is passed it just NULL;
**
** -hmm = Directory containing acoustic model files
** -lm = Word trigram language model input file
** -dict = Main pronunciation dictionary (lexicon) input file
** -logfn = Just redirecting logfiles
*/

int					main(int argc, char **argv)
{
	FILE			*fp;
	

	if (!(handler = malloc(sizeof(t_kift))))
	{
		fprintf(stderr, "Failed to initialize handler\n");
		return (-1);
	}
	handler->listen = 0;

	config = cmd_ln_init(NULL, ps_args(), TRUE,
			"-hmm", MODELDIR "/en-us/en-us",
			"-lm", DICTIONARY "/Dictionary/8136.lm",
			"-dict", DICTIONARY "/Dictionary/8136.dic",
			"-kws", "./keyphrase.list",
			"-logfn", "./testinglog",
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
		decomposing_string(decoded_speech);
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

/*
** Basic workflow of the idea
**	- Read input
**		look for the keyword
**	- IF no words after keyword then parse the next line
**	- OR if you have one word or something THEN stroin the next line and parse that
**		an uncomplete sentence
**	- THEN parse that command in the command wrapper
**
**	i.e:
**		keyword: "HEY CHUNGSTER"
**
**		"HEY CHUNGSTER SET A TIMER"
**			"HEY CHUNGSTER" - activates flag -> listening TRUE
**		THEN
**			parse str + (position of CHUNGSTER)
**			^	(SET A TIMER)
*/
