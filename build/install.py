# $Id$

from fileutils import (
	installDirs, installFile, installSymlink, installTree, scanTree
	)
from makeutils import extractMakeVariables, parseBool

from os import listdir
from os.path import basename, expanduser, isdir, splitext
import os
import sys

def installAll(
	installPrefix, binaryDestDir, shareDestDir, docDestDir,
	binaryBuildPath, targetPlatform, cbios, symlinkForBinary
	):
	platformVars = extractMakeVariables('build/platform-%s.mk' % targetPlatform)
	binaryFileName = 'openmsx' + platformVars['EXEEXT']

	docNodeVars = extractMakeVariables('doc/node.mk')
	docsToInstall = [
		'README', 'GPL', 'AUTHORS'
		] + [
		'doc/' + fileName for fileName in docNodeVars['INSTALL_DOCS'].split()
		]

	print '  Executable...'
	installDirs(installPrefix + binaryDestDir)
	installFile(
		binaryBuildPath,
		installPrefix + binaryDestDir + '/' + binaryFileName
		)

	print '  Data files...'
	installDirs(installPrefix + shareDestDir)
	installTree('share', installPrefix + shareDestDir, scanTree('share'))

	print '  Documentation...'
	installDirs(installPrefix + docDestDir)
	for path in docsToInstall:
		installFile(path, installPrefix + docDestDir + '/' + basename(path))
	installDirs(installPrefix + docDestDir + '/manual')
	for fileName in listdir('doc/manual'):
		if splitext(fileName)[1] in ('.html', '.css', '.png'):
			installFile(
				'doc/manual/' + fileName,
				installPrefix + docDestDir + '/manual/' + fileName
				)

	if cbios:
		print '  C-BIOS...'
		installFile(
			'Contrib/README.cbios', installPrefix + docDestDir + '/cbios.txt'
			)
		installTree(
			'Contrib/cbios', installPrefix + shareDestDir + '/machines',
			scanTree('Contrib/cbios')
			)

	if hasattr(os, 'symlink'):
		print '  Creating symlinks...'
		for machine, alias in (
			('Toshiba_HX-10', 'msx1'),
			('Philips_NMS_8250', 'msx2'),
			('Panasonic_FS-A1FX', 'msx2plus'),
			('Panasonic_FS-A1GT', 'turbor'),
			):
			installSymlink(
				machine,
				installPrefix + shareDestDir + '/machines/' + alias
				)
		if symlinkForBinary and installPrefix == '':
			def createSymlinkToBinary(linkDir):
				if linkDir != binaryDestDir and isdir(linkDir):
					try:
						installSymlink(
							binaryDestDir + '/' + binaryFileName,
							linkDir + '/' + binaryFileName
							)
					except OSError:
						return False
					else:
						return True
				else:
					return False
			success = createSymlinkToBinary('/usr/local/bin')
			if not success:
				createSymlinkToBinary(expanduser('~/bin'))

def main(
	installPrefix, binaryDestDir, shareDestDir, docDestDir,
	binaryBuildPath, targetPlatform, verboseStr, cbiosStr
	):
	customVars = extractMakeVariables('build/custom.mk')

	try:
		verbose = parseBool(verboseStr)
		cbios = parseBool(cbiosStr)
		symlinkForBinary = parseBool(customVars['SYMLINK_FOR_BINARY'])
	except ValueError, ex:
		print >> sys.stderr, 'Invalid argument:', ex
		sys.exit(2)

	if not installPrefix.endswith('/'):
		# Just in case the destination directories are not absolute.
		installPrefix += '/'

	if verbose:
		print 'Installing openMSX:'

	try:
		installAll(
			installPrefix, binaryDestDir, shareDestDir, docDestDir,
			binaryBuildPath, targetPlatform, cbios, symlinkForBinary
			)
	except IOError, ex:
		print >> sys.stderr, 'Installation failed:', ex
		sys.exit(1)

	if verbose:
		print 'Installation complete... have fun!'
		print (
			'Notice: if you want to emulate real MSX systems and not only the '
			'free C-BIOS machines, put the system ROMs in one of the following '
			'directories: %s/systemroms or '
			'~/.openMSX/share/systemroms'
			) % shareDestDir

if len(sys.argv) == 9:
	main(*sys.argv[1 : ])
else:
	print >> sys.stderr, \
		'Usage: python install.py ' \
		'DESTDIR INSTALL_BINARY_DIR INSTALL_SHARE_DIR INSTALL_DOC_DIR ' \
		'BINARY_FULL OPENMSX_TARGET_OS INSTALL_VERBOSE INSTALL_CONTRIB'
	sys.exit(2)
