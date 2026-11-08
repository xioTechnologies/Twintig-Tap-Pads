import cliny as cli
import ximu3

try:
    connection = ximu3.helpers.connect("Twintig Tap Pads")

    ximu3.helpers.send_command(connection, "factory")
    ximu3.helpers.send_command(connection, "hardware_version", "v1.0.0")  # edit this value as required
    ximu3.helpers.send_command(connection, "save")
    ximu3.helpers.send_command(connection, "blink")

    cli.print_success("Complete")

except Exception as ex:
    cli.print_error(ex)
