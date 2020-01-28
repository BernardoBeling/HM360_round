import sys
import os

numFrames = '20'
#numFrames = '1'
QPs = ['22', '27', '32', '37']
# QPs = ['37']
#path = '/data/videos/360/'
path = '/home/bernardo/videos/360/'

videos = [
	'AerialCity_3840x1920_30fps_8bit_420_erp.yuv',
	'PoleVault_le_3840x1920_30fps_8bit_420_erp.yuv'
		]

video_cfg = [
		'AerialCity.cfg',
		'PoleVault.cfg'
		]

video_viewport = [
		'AerialCity_DynamicViewports.cfg',
		'PoleVault_DynamicViewports.cfg'
		]

codingWidth = [
		'3328',
		'3328'
		]

codingHeight = [
		'1664',
		'1664'
		]

for video in xrange(0, len(videos)):
	for qp in xrange(0, len(QPs)):
		video_qp = videos[video].split('_')[0] + '_QP' + QPs[qp]

		cmd = 'taskset -c 0 ./TAppEncoderStatic -c ../cfg/encoder_intra_main10.cfg -c ../cfg/cfg-360Lib/encoder_360_ERP.cfg -c ../cfg/cfg-360Lib/per-sequence/360/360test_' + video_cfg[video] + ' -c ../cfg/cfg-360Lib/per-sequence/360/360test_' + video_viewport[video] + ' --SphFile=../cfg/cfg-360Lib/360Lib/sphere_655362.txt --InputFile='+ path + videos[video] + ' --CodingFaceWidth=' + codingWidth[video] + ' --CodingFaceHeight=' + codingHeight[video] +' -b ' + video_qp + 'REF.bin --QP=' +QPs[qp]+ ' --FramesToBeEncoded=' + numFrames + ' >Resultados/' + video_qp + 'REF.txt'
		print(cmd)
		os.system(cmd)
		
	

		