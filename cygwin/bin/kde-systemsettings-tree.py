#!/usr/bin/env python

# A small script that validates the structure of systemsettings.
#
# Copyright (c) 2010 Trever Fischer <tdfischer@fedoraproject.org>
#
# You are free to modify and distribute this script under
# the terms of the GPLv2 or later
from PyKDE4.kdecore import KServiceTypeTrader
from PyQt4.QtCore import QVariant

VALID_CATEGORIES = (
		"application-appearance-and-behavior",
		"application-appearance",
		"shortcuts-and-gestures",
		"account-details",
		"locale",
		"application-and-system-notifications",
		"personal-information",
		"workspace-appearance-and-behavior",
		"desktop-appearance",
		"window-behaviour",
		"hardware",
		"display",
		"audio-and-video",
		"main-input-devices",
		"other-input-devices",
		"removable-devices",
		"network-and-connectivity",
		"sharing",
		"network-settings",
		"bluetooth",
		"system-administration",
		"permissions",
		"security",
		"startup-and-shutdown"
	)

def printLevel(category, depth=0):
	results = KServiceTypeTrader.self().query('KCModule', "([X-KDE-System-Settings-Parent-Category] == '%s')"%(category))
	for result in results:
		print ("	"*depth)+'%s [%s]' % (result.property('Name', QVariant.String).toString(), result.desktopEntryPath())
		if result.property('Comment', QVariant.String).toString().isEmpty():
			print("	"*depth)+"***No comment!***"
	categories = KServiceTypeTrader.self().query('SystemSettingsCategory', "([X-KDE-System-Settings-Parent-Category] == '%s')"%(category))
	for subcategory in categories:
		print ("	"*depth)+'%s [%s]' % (subcategory.property('Name', QVariant.String).toString(), subcategory.desktopEntryPath())
		printLevel(subcategory.property('X-KDE-System-Settings-Category', QVariant.String).toString(), depth+1)

print "*** Current organization:"
printLevel('')

print "\n"
print "*** Searching for invalid categories:"
print "**** KCModules:"
results = KServiceTypeTrader.self().query('KCModule')
for result in results:
	if (not (result.property('X-KDE-System-Settings-Parent-Category', QVariant.String).toString() in VALID_CATEGORIES)):
		print "%s [%s]: %s"%(result.property('Name', QVariant.String).toString(), result.desktopEntryPath(), result.property('X-KDE-System-Settings-Parent-Category', QVariant.String).toString())
print "**** Categories:" 
results = KServiceTypeTrader.self().query('SystemSettingsCategory')
for result in results:
	if (not (result.property('X-KDE-System-Settings-Parent-Category', QVariant.String).toString() in VALID_CATEGORIES)):
		print "%s [%s]: %s"%(result.property('Name', QVariant.String).toString(), result.desktopEntryPath(), result.property('X-KDE-System-Settings-Parent-Category', QVariant.String).toString())
