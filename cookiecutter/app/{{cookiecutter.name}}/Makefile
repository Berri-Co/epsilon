snapshots += {{cookiecutter.camel_name}}::App::Snapshot
snapshot_headers += apps/{{cookiecutter.name}}/app.h

app_objs += $(addprefix apps/{{cookiecutter.name}}/,\
  app.o\
  {{cookiecutter.name}}_controller.o\
  {{cookiecutter.name}}_view.o\
)

i18n_files += $(addprefix apps/{{cookiecutter.name}}/,\
  base.universal.i18n\
)

app_images += apps/{{cookiecutter.name}}/{{cookiecutter.name}}_icon.png
