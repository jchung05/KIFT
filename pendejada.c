/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pendejada.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalpart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 01:11:52 by gmalpart          #+#    #+#             */
/*   Updated: 2018/04/23 04:48:17 by gmalpart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pocketsphinx.h>
#include <sphinxbase/ad.h>
#include <sphinxbase/err.h>
#include <sys/time.h>
#include <string.h>

const char			*recognize_from_microphone(void);

ps_decoder_t		*ps;
cmd_ln_t			*config;
ad_rec_t			*ad;

int16				adbuf[512];
uint8				utt_started;
uint8				in_speech;
int32				k;
char const			*hyp;
char const			*decoded_speech;

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

int			main(int ac, char **av)
{
	config = cmd_ln_init(NULL, ps_args(), TRUE,
			"-hmm", MODELDIR "/en-us/en-us",
			"-lm", MODELDIR "/en-us/en-us.lm.bin",
			"-dict", MODELDIR "/en-us/cmudict-en-us.dict",
			"-logfn", "/dev/null",
			NULL);

	if (!config)
	{
		fprintf(stderr, "Failed to create a config object, see log for details\n");
		return (-1);
	}
	// initializing decoder that'simple
	ps = ps_init(config);
	if (!ps)
	{
		fprintf(stderr, "Failed to create a recognizer, see log for details\n");
		return (-1);
	}

	printf("Regular setup done\n");
	// initialize a recording device  | int32 samples_per_sec - a.k.a sampling rate
	// link = https://github.com/cmusphinx/sphinxbase/blob/master/src/libsphinxbase/fe/fe_interface.c
	ad = ad_open_dev("sysdefault", (int)cmd_ln_float32_r(config, "-samprate"));

	while (1)
	{
		decoded_speech = recognize_from_microphone();
		printf("You said: %s\n", decoded_speech);
	}
	// close recorder
	ad_close(ad);
}

/*
** ad_functions are recorder managment
**
** what is ps_start_utt(ps) | ps - decoder
**  basically start interpreting stuff recorded
**
*/

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
		// ^ verifiers in case audio file is just garbage noise
 		if (!in_speech && utt_started)
		{
			ps_end_utt(ps);
			ad_stop_rec(ad);
			hyp = ps_get_hyp(ps, NULL );
			return (hyp);
			break;
		}
	}
}
