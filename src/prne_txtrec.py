#
#

import sys
from typing import Iterable

VERSION = "0.0.0"

# AWS hook - The max number of objects in a request
AWS_MAX_ITEMS = 1000

def handle_err (o: dict, e, m: str):
	"""Handle error according to the error definition

	The function will call exit() if the error definition dictates to do so

	Parameters:
		o: the error definition
		e: the exception (optional)
		m: the error message header, perror() param equiv (optional)
	"""
	if e:
		sys.stderr.write(str(e) + "\n\n")
	if m:
		l = m + ": " + o["msg"] + "\n"
	else:
		l = o["msg"] + "\n"
	sys.stderr.write(l)

	ec = o.get("ec", None)
	if ec is not None:
		exit(ec)

def termdot (str: str):
	"""Append a dot(".") to the string if it does not end with the dot"""
	if not str.endswith("."):
		return str + "."
	return str

def change_all (client, zone_id: str, action: str, it: Iterable):
	"""Change all RRs specified in the iterable"""
	c_arr = []
	for rr in it:
		c_arr.append({
			'Action': action,
			'ResourceRecordSet': rr
		})
	cb = { 'Changes': c_arr }

	return client.change_resource_record_sets(
			HostedZoneId = zone_id,
			ChangeBatch = cb
		)
