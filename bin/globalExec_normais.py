import sys
import os

numFrames = '20'
#numFrames = '1'
QPs = ['22', '27', '32', '37']
#path = '/data/videos/1600p/'
path = '/home/bernardo/videos/1600p/'

videos = [
	'PeopleOnStreet_2560x1600_30.yuv',
	'Traffic_2560x1600_30.yuv'
		]

video_cfg = [
		'PeopleOnStreet.cfg',
		'Traffic.cfg'
		]

#video_viewport = [
#		'AerialCity_DynamicViewports.cfg',
#		'PoleVault_DynamicViewports.cfg'
#		]

#codingWidth = [
#		'3328',
#		'3328'
#		]

#codingHeight = [
#		'1664',
#		'1664'
#		]

for video in xrange(0, len(videos)):
	for qp in xrange(0, len(QPs)):
		video_qp = videos[video].split('_')[0] + '_QP' + QPs[qp]
		cmd = 'taskset -c 0 ./TAppEncoderStatic -c ../cfg/encoder_intra_main10.cfg -c ../cfg/per-sequence/' + video_cfg[video] + ' --InputFile='+ path + videos[video] + ' -b ' + video_qp + 'REF.bin --QP=' +QPs[qp]+ ' --FramesToBeEncoded=' + numFrames + ' >Resultados/' + video_qp + 'REF.txt'
		print(cmd)
		os.system(cmd)